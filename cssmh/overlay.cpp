#include "overlay.hpp"
#include "input.hpp"
#include "base.hpp"

Overlay::Overlay(std::string window_name)
{
	this->display = XOpenDisplay(NULL);
	glfwInit();
	this->root_window = RootWindow(this->display, DefaultScreen(this->display));

	this->target_window_name = window_name;
	while (this->target_window == 0) {
		this->EnumWindows();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

Overlay::~Overlay()
{
	XCloseDisplay(this->display);
	glfwTerminate();
}

void Overlay::MainLoop()
{
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	this->overlay_window = glfwCreateWindow(100, 100, "CSSMH Overlay", NULL, NULL);

	glfwSetWindowAttrib(this->overlay_window, GLFW_DECORATED, GLFW_FALSE);
	glfwSetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
	glfwSetWindowAttrib(this->overlay_window, GLFW_FLOATING, GLFW_TRUE);

	glfwMakeContextCurrent(this->overlay_window);
	glfwShowWindow(this->overlay_window);
	glfwSwapInterval(1);

	this->overlay_window_x = glfwGetX11Window(this->overlay_window);

	this->imgui_ctx = ImGui::CreateContext();
	ImGui::SetCurrentContext(this->imgui_ctx);

	ImGuiIO &imgui_io = ImGui::GetIO();
	imgui_io.IniFilename = NULL;

	ImGui_ImplGlfw_InitForOpenGL(this->overlay_window, true);
	ImGui_ImplOpenGL2_Init();

	int display_w;
	int display_h;

	while (CSSMH::IsRunning && !glfwWindowShouldClose(this->overlay_window)) {
		glfwPollEvents();
		this->UpdateWindow();

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		this->imgui_bgdraw = ImGui::GetBackgroundDrawList();

		if (!this->RenderLoop())
			break;
		
		ImGui::Render();
		glfwGetFramebufferSize(this->overlay_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(this->overlay_window);
	}

	CSSMH::IsRunning = false;
	glfwDestroyWindow(this->overlay_window);
}

void Overlay::UpdateWindow()
{
	XWindowAttributes wattr;
	Window window_tmp;

	XGetWindowAttributes(this->display, this->target_window, &wattr);
	XTranslateCoordinates(this->display, this->target_window, this->root_window, 0, 0, &x, &y, &window_tmp);

	this->width = wattr.width;
	this->height = wattr.height;

	glfwSetWindowPos(this->overlay_window, this->x, this->y);
	glfwSetWindowSize(this->overlay_window, this->width, this->height);
}

bool Overlay::EnumWindowsCallback(Window window)
{
	if (this->GetWindowName(window) == this->target_window_name) {
		this->target_window = window;
		this->target_pid = this->GetWindowPID(window);
		return false;
	}

	return true;
}

bool Overlay::_EnumWindows(Window parent)
{
	Window window_tmp;
	Window *window_list = NULL;
	unsigned int window_count = 0;

	if (!this->callback_holder)
		return false;
	
	if (XQueryTree(this->display, parent, &window_tmp, &window_tmp, &window_list, &window_count) < Success || !window_list || !window_count)
		return true;
	
	for (unsigned int i = 0; i < window_count; ++i) {
		this->callback_holder = EnumWindowsCallback(window_list[i]);
		if (!this->callback_holder)
			break;
		
		this->callback_holder = this->_EnumWindows(window_list[i]);
		if (!this->callback_holder)
			break;
	}

	XFree(window_list);
	return this->callback_holder;
}

void Overlay::EnumWindows()
{
	this->callback_holder = true;
	this->_EnumWindows(this->root_window);
}

std::string Overlay::GetWindowName(Window window)
{
	char *window_name = NULL;
	std::string window_name_str = "";

	if (XFetchName(this->display, window, &window_name) >= Success && window_name) {
		window_name_str = window_name;
		XFree(window_name);
	}

	return window_name_str;
}

pid_t Overlay::GetWindowPID(Window window)
{
	pid_t pid = (pid_t)-1;
	Atom prop = XInternAtom(this->display, "_NET_WM_PID", True);
	unsigned char *pid_data;
	/* Unused variables */
	Atom atom_tmp;
	int i_tmp;
	unsigned long ul_tmp;

	if (XGetWindowProperty(this->display, window, prop, 0, BUFSIZ, False, AnyPropertyType, &atom_tmp, &i_tmp, &ul_tmp, &ul_tmp, &pid_data) >= Success) {
		pid = *(pid_t *)pid_data;
		XFree(pid_data);
	}

	return pid;
}

#include "base.hpp"

bool Overlay::RenderLoop()
{	
	if (!CSSMH::IsActive) {
		if (glfwGetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH) == GLFW_FALSE)
			glfwSetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
		return true;
	}

	if (CSSMH::KeyMenu.GetKeyState() == KeyInfo::RELEASED) {
		CSSMH::ShowMenu = !CSSMH::ShowMenu;
		if (CSSMH::ShowMenu) {
			glfwFocusWindow(CSSMH::GameOverlay->overlay_window);
		} else {
			XSetInputFocus(CSSMH::GameOverlay->display, CSSMH::GameOverlay->target_window, RevertToNone, CurrentTime);
		}
	}

	if (!CSSMH::ShowMenu) {
		if (glfwGetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH) == GLFW_FALSE)
			glfwSetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);
		return true;
	} else if (glfwGetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH) == GLFW_TRUE)
		glfwSetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);
	
	ImGui::Begin("CSSMH");
	ImGui::End();

	return true;
}

int main()
{
	CSSMH::Init();
}
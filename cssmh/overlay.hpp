#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include "headers.hpp"

class Overlay {
public:
	Display *display;
	std::string target_window_name;
	Window target_window = 0;
	pid_t target_pid = (pid_t)-1;
	GLFWwindow *overlay_window;
	Window overlay_window_x;
	Window root_window;
	ImGuiContext *imgui_ctx;
	int x;
	int y;
	unsigned int width;
	unsigned int height;
public:
	inline Overlay() {  }
	Overlay(std::string window_name);
	~Overlay();
	void MainLoop();
	bool RenderLoop();
private:
	bool callback_holder;
private:
	bool EnumWindowsCallback(Window window);
	bool _EnumWindows(Window parent);
	void EnumWindows();
	std::string GetWindowName(Window window);
	pid_t GetWindowPID(Window window);
	void UpdateWindow();
};

#endif

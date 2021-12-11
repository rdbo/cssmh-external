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
	} else if (glfwGetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH) == GLFW_TRUE)
		glfwSetWindowAttrib(this->overlay_window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);

	if (CSSMH::LocalPlayerPtr) {
		for (size_t i = 0; i < CSSMH::EntityList.size(); ++i) {
			if (CSSMH::EntityList[i].dormant && CSSMH::EntityList[i].health >= 0 && CSSMH::EntityList[i].team > 1)
				continue;
			
			CSSMH::EntityList[i].w2s_result = WorldToScreen(CSSMH::EntityList[i].position, CSSMH::EntityList[i].screen_pos, CSSMH::ViewMatrix, CSSMH::GameOverlay->width, CSSMH::GameOverlay->height);
			if (CSSMH::EntityList[i].w2s_result) {
				Hack::ESP_Snaplines(CSSMH::EntityList[i]);
			}
		}
	}
	
	if (CSSMH::ShowMenu) {
		ImGui::Begin("CSSMH");
		ImGui::Checkbox("Bunnyhop", &CSSMH::EnableBunnyhop);
		ImGui::Checkbox("ESP Snaplines", &CSSMH::EnableEspSnaplines);
		ImGui::End();
	}

	return true;
}

#include "input.hpp"
#include "base.hpp"

bool IsKeyPressed(KeySym key)
{
	char keymap[32];
	XQueryKeymap(CSSMH::GameOverlay->display, keymap);
	KeyCode kc = XKeysymToKeycode(CSSMH::GameOverlay->display, key);
	return (bool)(!!(keymap[kc >> 3] & (1 << (kc & 7))));
}

KeyInfo::KeyInfo(KeySym key)
{
	this->key = key;
}

KeyInfo::KeyState KeyInfo::GetKeyState()
{
	KeyState state = this->state;
	this->state = KeyState::NONE;
	return state;
}

void KeyInfo::UpdateKeyState()
{
	bool is_pressed = IsKeyPressed(this->key);
	if (this->state == KeyInfo::PRESSED && !is_pressed)
		this->state = KeyInfo::RELEASED;
	else if ((this->state == KeyInfo::RELEASED || this->state == KeyInfo::NONE) && is_pressed)
		this->state = KeyInfo::PRESSED;
}

void InputHandler()
{
	Atom active_prop = XInternAtom(CSSMH::GameOverlay->display, "_NET_ACTIVE_WINDOW", True);
	unsigned char *active_window_data;
	Atom atom_tmp;
	int i_tmp;
	unsigned long ul_tmp;

	while (CSSMH::IsRunning) {
		if (XGetWindowProperty(CSSMH::GameOverlay->display, CSSMH::GameOverlay->root_window, active_prop, 0, BUFSIZ, False, AnyPropertyType, &atom_tmp, &i_tmp, &ul_tmp, &ul_tmp, &active_window_data) >= Success) {
			Window active_window = *(Window *)active_window_data;
			CSSMH::IsActive = active_window == CSSMH::GameOverlay->target_window || active_window == CSSMH::GameOverlay->overlay_window_x;
		}

		if (!CSSMH::IsActive)
			continue;
		
		CSSMH::KeyMenu.UpdateKeyState();
		CSSMH::KeyBhop.UpdateKeyState();
	}
}

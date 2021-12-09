#ifndef INPUT_HPP
#define INPUT_HPP

#include "headers.hpp"

class KeyInfo {
public:
	enum KeyState {
		PRESSED,
		RELEASED,
		NONE
	};

	KeySym key;
private:
	KeyState state = KeyState::NONE;
public:
	KeyInfo(KeySym key);
public:
	KeyState GetKeyState();
	void UpdateKeyState();
};

void InputHandler();

#endif

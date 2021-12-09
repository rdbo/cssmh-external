#ifndef BASE_HPP
#define BASE_HPP

#include "headers.hpp"
#include "overlay.hpp"
#include "input.hpp"

namespace CSSMH {
	extern bool IsRunning;
	extern bool IsActive;
	extern bool ShowMenu;

	extern KeyInfo KeyMenu;
	extern KeyInfo KeyBhop;

	extern Overlay *GameOverlay;

	void Init();
}

#endif

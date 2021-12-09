#ifndef BASE_HPP
#define BASE_HPP

#include "headers.hpp"
#include "overlay.hpp"
#include "input.hpp"
#include "game.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "hack.hpp"

#define UNION_OFFSET(type, varname, offset) struct { char __tmp[offset]; type varname; }

namespace CSSMH {
	extern bool IsRunning;
	extern bool IsActive;
	extern bool ShowMenu;

	extern bool EnableBunnyhop;

	extern uintptr_t ClientBase;
	extern uintptr_t LocalPlayerPtr;
	extern uintptr_t InJumpBtn;

	extern KeyInfo KeyMenu;
	extern KeyInfo KeyBhop;

	extern Overlay *GameOverlay;

	extern Player LocalPlayer;

	void Init();
	void Shutdown();
}

#endif

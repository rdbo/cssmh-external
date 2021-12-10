#ifndef BASE_HPP
#define BASE_HPP

#include "headers.hpp"
#include "overlay.hpp"
#include "input.hpp"
#include "game.hpp"
#include "memory.hpp"
#include "offsets.hpp"
#include "hack.hpp"

namespace CSSMH {
	extern bool IsRunning;
	extern bool IsActive;
	extern bool ShowMenu;

	extern bool EnableBunnyhop;
	extern bool EnableEspSnaplines;

	extern uintptr_t ClientBase;
	extern uintptr_t EngineBase;
	extern uintptr_t LocalPlayerPtr;
	extern uintptr_t LocalPlayerAddr;
	extern uintptr_t InJumpBtn;

	extern KeyInfo KeyMenu;
	extern KeyInfo KeyBhop;

	extern Overlay *GameOverlay;

	extern Player LocalPlayer;
	extern std::array<Player, 64> EntityList;
	extern ViewMatrix_t ViewMatrix;

	void Init();
	void Shutdown();
}

#endif

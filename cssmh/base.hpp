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

	extern pointer_t ClientBase;
	extern pointer_t EngineBase;
	extern pointer_t LocalPlayerPtr;
	extern pointer_t LocalPlayerAddr;
	extern pointer_t InJumpBtn;

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

#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include "base.hpp"

namespace Offsets {
	// client.so
	const pointer_t LocalPlayerPtr = 0xBD0750;
	const pointer_t EntityList = 0xBA5FB4;
	const pointer_t EntityDist = 0x10;
	const pointer_t InJumpBtn = 0xBEE4E8;

	// engine.so
	const pointer_t ViewMatrix = 0xC9B160;

	// Player
	const pointer_t PlayerHealth = 0x84;
	const pointer_t PlayerTeam = 0x8C;
	const pointer_t PlayerFlags = 0x340;
	const pointer_t PlayerDormant = 0x16E;
	const pointer_t PlayerPosition = 0x250;
}

#endif

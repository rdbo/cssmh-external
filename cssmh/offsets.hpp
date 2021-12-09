#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include "base.hpp"

namespace Offsets {
	// client.so
	const uintptr_t LocalPlayerPtr = 0xBD0750;
	const uintptr_t EntityList = 0xBA5FB4;
	const uintptr_t EntityDist = 0x10;
	const uintptr_t InJumpBtn = 0xBEE4E8;

	// Player
	const uintptr_t PlayerHealth = 0x84;
	const uintptr_t PlayerFlags = 0x340;
}

#endif

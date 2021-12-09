#ifndef GAME_HPP
#define GAME_HPP

#include "headers.hpp"

#define FL_ONGROUND (1 << 0)

class Player {
public:
	uintptr_t address;
	int32_t health;
	int32_t flags;
public:
	inline Player() {  }
	Player(uintptr_t address);
	void Update();
};

#endif

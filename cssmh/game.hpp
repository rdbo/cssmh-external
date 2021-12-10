#ifndef GAME_HPP
#define GAME_HPP

#include "headers.hpp"

#define FL_ONGROUND (1 << 0)

struct iVec2 {
	int x;
	int y;
};

struct flVec3 {
	float x;
	float y;
	float z;
};

struct flVec4 {
	float x;
	float y;
	float z;
	float w;
};

typedef float ViewMatrix_t[4][4];

class Player {
public:
	uintptr_t address;
	int32_t health;
	int32_t team;
	int32_t flags;
	bool dormant;
	flVec3 position;
	iVec2 screen_pos;
	bool w2s_result;
public:
	inline Player() {  }
	Player(uintptr_t address);
	void Update();
};

bool WorldToScreen(flVec3 pos, iVec2& pos2d, ViewMatrix_t viewmatrix, unsigned int window_width, unsigned int window_height);

#endif

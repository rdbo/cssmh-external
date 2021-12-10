#include "game.hpp"
#include "base.hpp"

Player::Player(uintptr_t address)
{
	this->address = address;
}

void Player::Update()
{
	this->dormant = Memory::ReadMemory<bool>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerDormant);
	if (this->dormant) // Player information not being updated
		return;
	
	this->health = Memory::ReadMemory<int32_t>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerHealth);
	this->team = Memory::ReadMemory<int32_t>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerTeam);
	this->flags = Memory::ReadMemory<int32_t>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerFlags);
	this->position = Memory::ReadMemory<flVec3>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerPosition);
}

bool WorldToScreen(flVec3 pos, iVec2& pos2d, ViewMatrix_t viewmatrix, unsigned int window_width, unsigned int window_height)
{
	flVec4 clip_coords;
	clip_coords.x = pos.x * viewmatrix[0][0] + pos.y * viewmatrix[0][1] + pos.z * viewmatrix[0][2] + viewmatrix[0][3];
	clip_coords.y = pos.x * viewmatrix[1][0] + pos.y * viewmatrix[1][1] + pos.z * viewmatrix[1][2] + viewmatrix[1][3];
	clip_coords.z = pos.x * viewmatrix[2][0] + pos.y * viewmatrix[2][1] + pos.z * viewmatrix[2][2] + viewmatrix[2][3];
	clip_coords.w = pos.x * viewmatrix[3][0] + pos.y * viewmatrix[3][1] + pos.z * viewmatrix[3][2] + viewmatrix[3][3];

	if (clip_coords.w < 0.1f)
		return false;

	flVec3 ndc;
	ndc.x = clip_coords.x / clip_coords.w;
	ndc.y = clip_coords.y / clip_coords.w;
	ndc.z = clip_coords.z / clip_coords.w;

	pos2d.x = (int)((window_width / 2 * ndc.x) + (ndc.x + window_width / 2));
	pos2d.y = (int)(-(window_height / 2 * ndc.y) + (ndc.y + window_height / 2));
	return true;
}

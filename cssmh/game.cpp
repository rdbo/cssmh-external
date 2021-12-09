#include "game.hpp"
#include "base.hpp"

Player::Player(uintptr_t address)
{
	this->address = address;
}

void Player::Update()
{
	this->health = Memory::ReadMemory<int32_t>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerHealth);
	this->flags = Memory::ReadMemory<int32_t>(CSSMH::GameOverlay->target_pid, this->address + Offsets::PlayerFlags);
}

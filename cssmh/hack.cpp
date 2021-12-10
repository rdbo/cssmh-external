#include "hack.hpp"

void Hack::MainLoop()
{
	while (CSSMH::IsRunning) {
		CSSMH::LocalPlayerAddr = Memory::ReadMemory<uintptr_t>(CSSMH::GameOverlay->target_pid, CSSMH::LocalPlayerPtr);
		if (!CSSMH::LocalPlayerAddr)
			continue;
		
		CSSMH::LocalPlayer = Player(CSSMH::LocalPlayerAddr);
		CSSMH::LocalPlayer.Update();
		Memory::ReadMemory(CSSMH::GameOverlay->target_pid, CSSMH::EngineBase + Offsets::ViewMatrix, CSSMH::ViewMatrix, sizeof(CSSMH::ViewMatrix));
		for (size_t i = 0; i < CSSMH::EntityList.size(); ++i) {
			CSSMH::EntityList[i] = Player(CSSMH::ClientBase + Offsets::EntityList + Offsets::EntityDist * i);
			CSSMH::EntityList[i].Update();
		}

		Hack::Bunnyhop();
	}
}

#include "hack.hpp"

void Hack::MainLoop()
{
	pointer_t EntityPointer;
	pointer_t EntityAddress;

	while (CSSMH::IsRunning) {
		CSSMH::LocalPlayerAddr = Memory::ReadMemory<pointer_t>(CSSMH::GameOverlay->target_pid, CSSMH::LocalPlayerPtr);
		if (!CSSMH::LocalPlayerAddr)
			continue;
		
		CSSMH::LocalPlayer = Player(CSSMH::LocalPlayerAddr);
		CSSMH::LocalPlayer.Update();
		Memory::ReadMemory(CSSMH::GameOverlay->target_pid, CSSMH::EngineBase + Offsets::ViewMatrix, CSSMH::ViewMatrix, sizeof(CSSMH::ViewMatrix));
		for (size_t i = 0; i < CSSMH::EntityList.size(); ++i) {
			EntityPointer = CSSMH::ClientBase + Offsets::EntityList + i * Offsets::EntityDist;
			EntityAddress = Memory::ReadMemory<pointer_t>(CSSMH::GameOverlay->target_pid, EntityPointer);
			if (!EntityAddress)
				continue;
			CSSMH::EntityList[i] = Player(EntityAddress);
			CSSMH::EntityList[i].Update();
		}

		Hack::Bunnyhop();
	}
}

#include "hack.hpp"

void Hack::MainLoop()
{
	uintptr_t LocalPlayerVal;

	while (CSSMH::IsRunning) {
		LocalPlayerVal = Memory::ReadMemory<uintptr_t>(CSSMH::GameOverlay->target_pid, CSSMH::LocalPlayerPtr);
		if (!LocalPlayerVal)
			continue;
		
		CSSMH::LocalPlayer = Player(LocalPlayerVal);
		CSSMH::LocalPlayer.Update();
		Hack::Bunnyhop();
	}
}

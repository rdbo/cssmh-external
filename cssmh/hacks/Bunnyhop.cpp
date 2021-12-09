#include <base.hpp>

void Hack::Bunnyhop()
{
	if (CSSMH::EnableBunnyhop && CSSMH::KeyBhop.GetKeyState() == KeyInfo::PRESSED && CSSMH::LocalPlayer.flags & FL_ONGROUND)
		Memory::WriteMemory<int32_t>(CSSMH::GameOverlay->target_pid, CSSMH::InJumpBtn, 6);
}

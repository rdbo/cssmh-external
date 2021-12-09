#include "base.hpp"

bool CSSMH::IsActive = false;
bool CSSMH::IsRunning = true;
bool CSSMH::ShowMenu = true;

bool CSSMH::EnableBunnyhop = false;

uintptr_t CSSMH::ClientBase = 0;
uintptr_t CSSMH::LocalPlayerPtr = 0;
uintptr_t CSSMH::InJumpBtn = 0;

KeyInfo CSSMH::KeyMenu = KeyInfo(XK_Insert);
KeyInfo CSSMH::KeyBhop = KeyInfo(XK_space);
Player CSSMH::LocalPlayer = Player();

Overlay *CSSMH::GameOverlay;

void OverlayThread()
{
	CSSMH::GameOverlay->MainLoop();
}

void InputThread()
{
	InputHandler();
}

void HackThread()
{
	Hack::MainLoop();
}

void CSSMH::Init() {
	std::cout << "[CSSMH]" << std::endl;
	std::cout << std::endl;

	std::cout << "[.] Initializing Xlib threads..." << std::endl;
	XInitThreads();
	std::cout << "[#] Xlib threads initialized" << std::endl;
	std::cout << std::endl;

	std::cout << "[.] Initializing overlay..." << std::endl;
	CSSMH::GameOverlay = new Overlay("Counter-Strike Source - OpenGL");
	std::cout << "[#] Overlay initialized" << std::endl;
	std::cout << std::endl;

	std::cout << "[.] Initializing modules..." << std::endl;
	while (!CSSMH::ClientBase)
		CSSMH::ClientBase = Memory::GetModuleBase(CSSMH::GameOverlay->target_pid, "/cstrike/bin/client.so");
	
	CSSMH::LocalPlayerPtr = CSSMH::ClientBase + Offsets::LocalPlayerPtr;
	CSSMH::InJumpBtn = CSSMH::ClientBase + Offsets::InJumpBtn;

	std::cout << "[*] Client Base: " << (void *)CSSMH::ClientBase << std::endl;

	std::cout << "[#] Modules initialized" << std::endl;
	std::cout << std::endl;

	std::cout << "[.] Initializing threads..." << std::endl;
	std::thread overlay_thread = std::thread(OverlayThread);
	std::thread input_thread = std::thread(InputThread);
	std::thread hack_thread = std::thread(HackThread);
	std::cout << "[#] Threads initialized" << std::endl;

	overlay_thread.join();
	input_thread.join();
	hack_thread.join();

	CSSMH::Shutdown();
}

void CSSMH::Shutdown()
{
	delete CSSMH::GameOverlay;
}
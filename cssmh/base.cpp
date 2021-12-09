#include "base.hpp"

bool CSSMH::IsActive = false;
bool CSSMH::IsRunning = true;
bool CSSMH::ShowMenu = true;

KeyInfo CSSMH::KeyMenu = KeyInfo(XK_Insert);
KeyInfo CSSMH::KeyBhop = KeyInfo(XK_space);

Overlay *CSSMH::GameOverlay;

void OverlayThread()
{
	std::cout << "[*] Running Overlay Mainloop" << std::endl;
	CSSMH::GameOverlay->MainLoop();
}

void InputThread()
{
	InputHandler();
}

void CSSMH::Init() {
	std::cout << "[*] CSSMH Initializing..." << std::endl;
	XInitThreads();
	CSSMH::GameOverlay = new Overlay("Counter-Strike Source - OpenGL");
	std::thread overlay_thread = std::thread(OverlayThread);
	std::thread input_thread = std::thread(InputThread);
	std::cout << "[*] Threads initialized" << std::endl;
	overlay_thread.join();
	input_thread.join();
	delete CSSMH::GameOverlay;
}
#include "hack.hpp"

void Hack::ESP_Snaplines(Player &player)
{
	CSSMH::GameOverlay->imgui_bgdraw->AddLine(ImVec2(10, 10), ImVec2(20, 20), ImColor(255, 0, 0, 255));
	
	if (!CSSMH::EnableEspSnaplines)
		return;
	
	ImVec2 p1 = { (float)CSSMH::GameOverlay->width / 2, (float)CSSMH::GameOverlay->height };
	ImVec2 p2 = { (float)player.screen_pos.x, (float)player.screen_pos.y };
	CSSMH::GameOverlay->imgui_bgdraw->AddLine(p1, p2, ImColor(255, 0, 0, 255));
}
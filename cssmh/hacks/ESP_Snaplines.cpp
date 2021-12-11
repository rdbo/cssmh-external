#include "hack.hpp"

void Hack::ESP_Snaplines(Player &player)
{
	if (!CSSMH::EnableEspSnaplines)
		return;
	
	ImVec2 p1 = { (float)CSSMH::GameOverlay->width / 2, (float)CSSMH::GameOverlay->height };
	ImVec2 p2 = { (float)player.screen_pos.x, (float)player.screen_pos.y };
	ImColor color;

	if (player.team == CSSMH::LocalPlayer.team)
		color = ImColor(0, 0, 255, 255);
	else
		color = ImColor(255, 0, 0, 255);
	
	CSSMH::GameOverlay->imgui_bgdraw->AddLine(p1, p2, color);
}
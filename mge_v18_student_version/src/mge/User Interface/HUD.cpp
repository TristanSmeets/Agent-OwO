#include "HUD.hpp"

HUD::HUD(int levelNumber)
{
	luaHUD = LuaWrapper::InitializeLuaState("/LuaGameScripts/UI/HUD.lua");
	stepCounter = new UIStepCounter(luaHUD, levelNumber);
	//std::cout << "Font Size: " << std::to_string(LuaWrapper::GetNumber<int>(luaHUD, "FontSize"));
}

HUD::~HUD()
{
	std::cout << "GC running on:HUD.\n";
	LuaWrapper::CloseLuaState(luaHUD);
}

void HUD::Draw(sf::RenderWindow* window)
{
	stepCounter->Draw(window);
}

#include "HUD.hpp"

HUD::HUD(int levelNumber)
{
	luaHUD = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/HUD.lua");
	stepCounter = new UIStepCounter(luaHUD, levelNumber);
	dialogue = new Dialogue();
	dialogue->LoadDialogues(levelNumber);
}

HUD::~HUD()
{
	std::cout << "GC running on:HUD.\n";
	if(stepCounter != nullptr) delete stepCounter;
	if (dialogue != nullptr) delete stepCounter;
	LuaWrapper::CloseLuaState(luaHUD);
}

void HUD::Draw(sf::RenderWindow* window)
{
	stepCounter->Draw(window);
}

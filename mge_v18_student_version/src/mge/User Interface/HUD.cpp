#include "HUD.hpp"

HUD::HUD(int levelNumber) : levelNumber(levelNumber)
{
	std::cout << "Creating HUD.\n";
	luaHUD = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/HUD.lua");
	stepCounter = new UIStepCounter(luaHUD, levelNumber);
	dialogue = new Dialogue();
	dialogue->LoadDialogues(levelNumber);
}

HUD::~HUD()
{
	std::cout << "GC running on:HUD.\n";
	if (stepCounter != nullptr) delete stepCounter;
	if (dialogue != nullptr) delete dialogue;
	LuaWrapper::CloseLuaState(luaHUD);
}

void HUD::Draw(sf::RenderWindow* window)
{
	if (levelNumber >= 2)
		stepCounter->Draw(window);
}

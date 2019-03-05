#include "HUD.hpp"

HUD::HUD(int levelNumber) : levelNumber(levelNumber), Observer<GeneralEvent>()
{
	std::cout << "Creating HUD.\n";
	EventQueue::AddObserver(this);
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
	EventQueue::RemoveObserver(this);
}

void HUD::Draw(sf::RenderWindow* window)
{
	if (showingDialogue)
		dialogue->Draw(window);
	else
		if (levelNumber > 2)
			stepCounter->Draw(window);
}

void HUD::OnNotify(const GeneralEvent& info)
{
	if (info.isDialogueCompleted)
		showingDialogue = false;
	if (info.showEndDialogue)
		showingDialogue = true;
}
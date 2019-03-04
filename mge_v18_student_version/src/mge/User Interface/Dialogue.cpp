#include "Dialogue.hpp"

Dialogue::Dialogue() : Observer<GeneralEvent>()
{
	std::cout << "Creating Dialogue.\n";

	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	amountOfLevels = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");

	luaDialogue = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/Dialogue.lua");

	LuaWrapper::CloseLuaState(luaLevelInfo);
	EventQueue::AddObserver(this);
}

Dialogue::~Dialogue()
{
	std::cout << "GC running on:Dialogue.\n";

	unloadDialogues();
	startDialogue.clear();
	endDialogue.clear();
}

void Dialogue::OnNotify(const GeneralEvent & info)
{
	if (info.nextLevel)
	{
		unloadDialogues();
		levelNumber++;
		if (levelNumber > amountOfLevels)
			levelNumber = 1;
		loadStartDialogue(levelNumber);
		loadEndDialogue(levelNumber);
	}
	if (info.nextDialogue)
	{
		currentImage++;
		setCurrentImage(currentImage);
	}
	if (info.showStartDialogue)
	{
		currentImage = 0;
		dialogueType = DIALOGUE::START_DIALOGUE;
		setCurrentImage(currentImage);
	}
	if (info.showEndDialogue)
	{
		currentImage = 0;
		dialogueType = DIALOGUE::END_DIALOGUE;
		setCurrentImage(currentImage);
	}
}

void Dialogue::LoadDialogues(int level)
{
	loadStartDialogue(level);
	loadEndDialogue(level);
}

void Dialogue::loadStartDialogue(int level)
{
	std::cout << "Loading Start Dialogue.\n";
	std::string luaVariable = "Level" + std::to_string(level) + "_Start";

	lua_getglobal(luaDialogue, luaVariable.c_str());

	lua_pushnil(luaDialogue);
	
	while (lua_next(luaDialogue, -2) != 0)
	{
		if (lua_isstring(luaDialogue, -1))
		{
			std::string currentPath = lua_tostring(luaDialogue, -1);
			std::cout << "Current path: " << currentPath << std::endl;
		}
		lua_pop(luaDialogue, 1);
	}

	lua_pop(luaDialogue, 1);
}

void Dialogue::loadEndDialogue(int level)
{
	std::cout << "Loading End Dialogue.\n";

	std::string luaVariable = "Level" + std::to_string(level) + "_Exit";

	lua_getglobal(luaDialogue, luaVariable.c_str());

	lua_pushnil(luaDialogue);

	while (lua_next(luaDialogue, -2) != 0)
	{
		if (lua_isstring(luaDialogue, -1))
		{
			std::string currentPath = lua_tostring(luaDialogue, -1);
			std::cout << "Current path: " << currentPath << std::endl;
		}
		lua_pop(luaDialogue, 1);
	}
	lua_pop(luaDialogue, 1);
}

void Dialogue::setCurrentImage(int imageIndex)
{
}

void Dialogue::unloadDialogues()
{
}


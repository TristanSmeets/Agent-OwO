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
	EventQueue::RemoveObserver(this);
	startDialogue.clear();
	endDialogue.clear();
}

void Dialogue::OnNotify(const GeneralEvent & info)
{
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

			sf::Image currentImage = sf::Image();
			currentImage.loadFromFile(currentPath);
			startDialogue.push_back(currentImage);
		}
		lua_pop(luaDialogue, 1);
	}
	lua_pop(luaDialogue, 1);
	std::cout << "Start Dialogue size: " << startDialogue.size() << std::endl;
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
			sf::Image currentImage = sf::Image();
			currentImage.loadFromFile(currentPath);
			endDialogue.push_back(currentImage);
		}
		lua_pop(luaDialogue, 1);
	}
	lua_pop(luaDialogue, 1);
	std::cout << "End Dialogue size: " << endDialogue.size() << std::endl;
}

void Dialogue::setCurrentImage(int imageIndex)
{
	sf::Texture texture;
	switch (dialogueType)
	{
	case DIALOGUE::START_DIALOGUE:
		texture.loadFromImage(startDialogue[imageIndex]);
		break;
	case DIALOGUE::END_DIALOGUE:
		texture.loadFromImage(endDialogue[imageIndex]);
		break;
	}
	currentDialogue.setTexture(texture);
}

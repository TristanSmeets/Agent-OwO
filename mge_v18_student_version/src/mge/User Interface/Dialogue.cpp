#include "Dialogue.hpp"

Dialogue::Dialogue() : Observer<GeneralEvent>()
{
	std::cout << "Creating Dialogue.\n";

	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	amountOfLevels = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");

	luaDialogue = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/Dialogue.lua");

	LuaWrapper::CloseLuaState(luaLevelInfo);
	EventQueue::AddObserver(this);
	currentTexture = new sf::Texture();
}

Dialogue::~Dialogue()
{
	std::cout << "GC running on:Dialogue.\n";
	EventQueue::RemoveObserver(this);
	startDialogue.clear();
	endDialogue.clear();
	delete currentTexture;
}

void Dialogue::OnNotify(const GeneralEvent & info)
{
	if (info.nextDialogue)
	{
		std::cout << "Loading next image.\n";
		currentImage++;
		setCurrentImage(currentImage);
	}
	if (info.showEndDialogue)
	{
		currentImage = 0;
		dialogueType = DIALOGUE::END_DIALOGUE;
		setCurrentImage(currentImage);
		showingDialogue = true;
	}
}

void Dialogue::LoadDialogues(int level)
{
	loadStartDialogue(level);
	loadEndDialogue(level);
	setCurrentImage(currentImage);
	currentDialogue.setPosition(0, 100);
	showingDialogue = true;
}

void Dialogue::Draw(sf::RenderWindow * window)
{
	if (showingDialogue)
		window->draw(currentDialogue);
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
			if (currentImage.loadFromFile(currentPath))
				std::cout << "Loaded image.\n";
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
			if (currentImage.loadFromFile(currentPath))
				std::cout << "Loaded image.\n";
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
	std::cout << "ImageIndex > StartDialogue Size: " << (imageIndex + 1 > startDialogue.size()) << std::endl;
	
	switch (dialogueType)
	{
	case DIALOGUE::START_DIALOGUE:
		if (imageIndex + 1 > startDialogue.size())
		{
			GeneralEvent info = GeneralEvent();
			info.isDialogueCompleted = true;
			EventQueue::QueueEvent(info);
			showingDialogue = false;
		}
		else
			currentTexture->loadFromImage(startDialogue[imageIndex]);
		break;
	case DIALOGUE::END_DIALOGUE:
		if (imageIndex + 1 > endDialogue.size())
		{
			GeneralEvent info = GeneralEvent();
			info.nextLevel = true;
			EventQueue::QueueEvent(info);
			showingDialogue = false;
		}
		else
			currentTexture->loadFromImage(endDialogue[imageIndex]);
		break;
	}
	currentDialogue.setTexture(*currentTexture);

	/*sf::Vector2u textureSize = currentTexture->getSize();
	currentDialogue.setOrigin(textureSize.x * .5f, textureSize.y * .5f);*/
}

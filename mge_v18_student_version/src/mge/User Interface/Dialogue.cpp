#include "Dialogue.hpp"

Dialogue::Dialogue() : Observer<GeneralEvent>()
{
	lua_State* luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	amountOfLevels = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");

	luaDialogue = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/Dialogue.lua");
	luaDialogueLocation = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/DialogueLocation.lua");

	LuaWrapper::CloseLuaState(luaLevelInfo);
	EventQueue::AddObserver(this);
	currentTexture = new sf::Texture();
}

Dialogue::~Dialogue()
{
	EventQueue::RemoveObserver(this);
	startDialogue.clear();
	endDialogue.clear();

	LuaWrapper::CloseLuaState(luaDialogue);
	delete currentTexture;
}

void Dialogue::OnNotify(const GeneralEvent & info)
{
	if (info.resetLevel)
	{
		dialogueType = DIALOGUE::START_DIALOGUE;
		showingDialogue = false;
	}

	if (info.nextDialogue)
	{
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
	if (info.showGameOver)
	{
		currentImage = 0;
		showingDialogue = false;
	}
}

void Dialogue::LoadDialogues(int level)
{
	loadStartDialogue(level);
	loadEndDialogue(level);
	setCurrentImage(currentImage);

	lua_getglobal(luaDialogueLocation, "Buttons");

	lua_pushnil(luaDialogueLocation);

	glm::vec3 position;

	while (lua_next(luaDialogueLocation, -2) != 0)
	{
		position = LuaWrapper::GetTableVec3(luaDialogueLocation, "Position");
		lua_pop(luaDialogueLocation, 1);
	}
	lua_pop(luaDialogueLocation, 1);

	currentDialogue.setPosition(position.x, position.y);
	showingDialogue = true;
}

void Dialogue::Draw(sf::RenderWindow * window)
{
	if (showingDialogue)
		window->draw(currentDialogue);
}

void Dialogue::loadStartDialogue(int level)
{
	std::string luaVariable = "Level" + std::to_string(level) + "_Start";

	lua_getglobal(luaDialogue, luaVariable.c_str());

	lua_pushnil(luaDialogue);

	while (lua_next(luaDialogue, -2) != 0)
	{
		if (lua_isstring(luaDialogue, -1))
		{
			std::string currentPath = lua_tostring(luaDialogue, -1);
			sf::Image currentImage = sf::Image();
			currentImage.loadFromFile(currentPath);
			startDialogue.push_back(currentImage);
		}
		lua_pop(luaDialogue, 1);
	}
	lua_pop(luaDialogue, 1);
}

void Dialogue::loadEndDialogue(int level)
{
	std::string luaVariable = "Level" + std::to_string(level) + "_Exit";

	lua_getglobal(luaDialogue, luaVariable.c_str());

	lua_pushnil(luaDialogue);

	while (lua_next(luaDialogue, -2) != 0)
	{
		if (lua_isstring(luaDialogue, -1))
		{
			std::string currentPath = lua_tostring(luaDialogue, -1);
			sf::Image currentImage = sf::Image();
			currentImage.loadFromFile(currentPath);
			endDialogue.push_back(currentImage);
		}
		lua_pop(luaDialogue, 1);
	}
	lua_pop(luaDialogue, 1);
}

void Dialogue::setCurrentImage(int imageIndex)
{
	switch (dialogueType)
	{
	case DIALOGUE::START_DIALOGUE:
		if (imageIndex != startDialogue.size() && imageIndex == 0)
		{
			lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
			float pitch = LuaWrapper::GetNumber<float>(luaAudio, "DialoguePitch");
			AudioLocator::GetAudio()->GetSoundEffect(SFX_DIALOGUE).SetPitch(pitch);
			AudioLocator::GetAudio()->PlaySoundEffect(SFX_DIALOGUE);
			LuaWrapper::CloseLuaState(luaAudio);
		}
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
		if (imageIndex != endDialogue.size() && imageIndex == 0)
		{
			lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
			float pitch = LuaWrapper::GetNumber<float>(luaAudio, "DialoguePitch");
			AudioLocator::GetAudio()->GetSoundEffect(SFX_DIALOGUE).SetPitch(pitch);
			AudioLocator::GetAudio()->PlaySoundEffect(SFX_DIALOGUE);
			LuaWrapper::CloseLuaState(luaAudio);
		}

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

	sf::Vector2u textureSize = currentTexture->getSize();
	currentDialogue.setOrigin(textureSize.x * .5f, textureSize.y * .5f);
}

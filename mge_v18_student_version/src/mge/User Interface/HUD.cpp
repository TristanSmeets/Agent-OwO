#include "HUD.hpp"

HUD::HUD(int levelNumber) : levelNumber(levelNumber), Observer<GeneralEvent>()
{
	EventQueue::AddObserver(this);
	luaHUD = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/HUD.lua");
	stepCounter = new UIStepCounter(luaHUD, levelNumber);
	dialogue = new Dialogue();
	dialogue->LoadDialogues(levelNumber);
	initialize();
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
	{
		window->draw(iconSprite);
		if (levelNumber > 2)
			stepCounter->Draw(window);
	}
}

void HUD::OnNotify(const GeneralEvent& info)
{
	if (info.isDialogueCompleted || info.resetLevel)
		showingDialogue = false;
	if (info.showEndDialogue || info.showGameOver)
		showingDialogue = true;
}

void HUD::initialize()
{
	lua_State* luaInGame = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/InGame.lua");

	lua_getglobal(luaInGame, "Buttons");

	lua_pushnil(luaInGame);

	while (lua_next(luaInGame, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaInGame, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaInGame, "Type");
		std::string imagePath = LuaWrapper::GetTableString(luaInGame, "ImagePath");

		if (UIType == "BACKGROUND")
		{
			std::cout << "Creating CharacterIcon.\n";
			iconTexture = new sf::Texture();
			iconTexture->loadFromFile(imagePath);
			iconSprite.setTexture(*iconTexture);
			iconSprite.setPosition(position.x, position.y);
			sf::Vector2u iconSize = iconTexture->getSize();
			iconSprite.setOrigin(iconSize.x * .5f, iconSize.y * .5f);
		}
		lua_pop(luaInGame, 1);
	}
	lua_pop(luaInGame, 1);

	LuaWrapper::CloseLuaState(luaInGame);
}

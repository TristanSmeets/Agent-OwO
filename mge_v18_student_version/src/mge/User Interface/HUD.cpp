#include "HUD.hpp"

HUD::HUD(int levelNumber) : levelNumber(levelNumber), Observer<GeneralEvent>()
{
	EventQueue::AddObserver(this);
	luaHUD = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/HUD.lua");
	stepCounter = new UIStepCounter(levelNumber);
	dialogue = new Dialogue();
	dialogue->LoadDialogues(levelNumber);
	initialize();
}

HUD::~HUD()
{
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
	lua_getglobal(luaHUD, "Buttons");

	lua_pushnil(luaHUD);

	while (lua_next(luaHUD, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaHUD, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaHUD, "Type");

		if (UIType == "BACKGROUND")
		{
			std::string imagePath = LuaWrapper::GetTableString(luaHUD, "ImagePath");
			iconTexture = new sf::Texture();
			iconTexture->loadFromFile(imagePath);
			iconSprite.setTexture(*iconTexture);
			iconSprite.setPosition(position.x, position.y);
			sf::Vector2u iconSize = iconTexture->getSize();
			iconSprite.setOrigin(iconSize.x * .5f, iconSize.y * .5f);
		}
		lua_pop(luaHUD, 1);
	}
	lua_pop(luaHUD, 1);
}

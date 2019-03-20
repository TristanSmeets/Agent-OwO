#include "CreditsScreen.hpp"

CreditsScreen::CreditsScreen(World * world, sf::RenderWindow * window) : world(world)
{
	initialize();

	mouse = new GameObject("MOUSE");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

CreditsScreen::~CreditsScreen()
{
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;

	delete backgroundTexture;

	ButtonManager::RemoveButton(backButton);
	delete backButton;
}

void CreditsScreen::Draw(sf::RenderWindow * window)
{
	window->draw(backgroundImage);

	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			window->draw(*current->GetSprite());
		}
	}
}

void CreditsScreen::initialize()
{
	lua_State* luaCredits = LuaWrapper::InitializeLuaState("LuaGameScripts\\UI\\Credits.lua");

	lua_getglobal(luaCredits, "Buttons");

	lua_pushnil(luaCredits);

	while (lua_next(luaCredits, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaCredits, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaCredits, "Type");
		std::string imagePath = LuaWrapper::GetTableString(luaCredits, "ImagePath");

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaCredits, "ButtonType");

			if (ButtonType == "RETURN")
			{
				backButton = new Button(imagePath);
				backButton->SetCommand(new QuitCommand());
				backButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(backButton);
			}
		}

		if (UIType == "IMAGE")
		{
			backgroundTexture = new sf::Texture();
			backgroundTexture->loadFromFile(imagePath);
			backgroundImage.setTexture(*backgroundTexture);
			backgroundImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u bgSize = backgroundTexture->getSize();
			backgroundImage.setOrigin(bgSize.x * .5f, bgSize.y * .5f);
		}

		lua_pop(luaCredits, 1);
	}
	lua_pop(luaCredits, 1);

	LuaWrapper::CloseLuaState(luaCredits);
}


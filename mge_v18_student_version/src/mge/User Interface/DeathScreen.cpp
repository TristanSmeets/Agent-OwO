#include "DeathScreen.hpp"

DeathScreen::DeathScreen(World* world, sf::Window* window) : world(world)
{
	initialize();

	//Mouse setup
	mouse = new GameObject("MOUSE");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

DeathScreen::~DeathScreen()
{
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(retryButton);
	ButtonManager::RemoveButton(quitButton);

	delete backgroundTexture;
}

void DeathScreen::Draw(sf::RenderWindow * window)
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

void DeathScreen::initialize()
{
	lua_State* luaResolution = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/ResolutionScreen.lua");

	lua_getglobal(luaResolution, "Buttons");

	lua_pushnil(luaResolution);

	while (lua_next(luaResolution, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaResolution, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaResolution, "Type");
		std::string imagePath = LuaWrapper::GetTableString(luaResolution, "ImagePath");

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaResolution, "ButtonType");

			if (ButtonType == "CONTINUE")
			{
				retryButton = new Button(imagePath);
				retryButton->SetCommand(new RetryCommand());
				retryButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(retryButton);
			}

			if (ButtonType == "EXIT")
			{
				quitButton = new Button(imagePath);
				quitButton->SetCommand(new QuitCommand());
				quitButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(quitButton);
			}
		}

		if (UIType == "BACKGROUND")
		{
			backgroundTexture = new sf::Texture();
			backgroundTexture->loadFromFile(imagePath);
			backgroundImage.setTexture(*backgroundTexture);
			backgroundImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u bgSize = backgroundTexture->getSize();
			backgroundImage.setOrigin(bgSize.x * .5f, bgSize.y * 0.5f);
		}

		lua_pop(luaResolution, 1);
	}
	lua_pop(luaResolution, 1);

	LuaWrapper::CloseLuaState(luaResolution);
}

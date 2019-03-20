#include "PauseScreen.hpp"

PauseScreen::PauseScreen(World* world, sf::RenderWindow* window) : world(world)
{
	initialize();
	
	mouse = new GameObject("MOUSE");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);
}

PauseScreen::~PauseScreen()
{
	std::cout << "GC running on:PauseScreen.\n";

	delete mouseBehaviour;
	world->remove(mouse);
	delete mouse;
	delete backgroundTexture;

	ButtonManager::RemoveButton(continueButton);
	ButtonManager::RemoveButton(quitButton);
	delete continueButton;
	delete quitButton;
}

void PauseScreen::Draw(sf::RenderWindow * window)
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

void PauseScreen::initialize()
{
	lua_State* luaPauseScreen = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/PauseScreen.lua");

	lua_getglobal(luaPauseScreen, "Buttons");

	lua_pushnil(luaPauseScreen);

	while (lua_next(luaPauseScreen, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaPauseScreen, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaPauseScreen, "Type");

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaPauseScreen, "ButtonType");

			if (ButtonType == "CONTINUE")
			{
				std::string imagePath = LuaWrapper::GetTableString(luaPauseScreen, "ImagePath");
				continueButton = new Button(imagePath);
				continueButton->SetCommand(new ContinueCommand());
				continueButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(continueButton);
			}

			if (ButtonType == "EXIT")
			{
				std::string imagePath = LuaWrapper::GetTableString(luaPauseScreen, "ImagePath");
				quitButton = new Button(imagePath);
				quitButton->SetCommand(new QuitCommand());
				quitButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(quitButton);
			}
		}
		if (UIType == "BACKGROUND")
		{
			backgroundTexture = new sf::Texture();
			std::string imagePath = LuaWrapper::GetTableString(luaPauseScreen, "ImagePath");
			backgroundTexture->loadFromFile(imagePath);
			backgroundImage.setTexture(*backgroundTexture);
			backgroundImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u bgSize = backgroundTexture->getSize();
			backgroundImage.setOrigin(bgSize.x * 0.5f, bgSize.y * 0.5f);
		}
		lua_pop(luaPauseScreen, 1);
	}
	lua_pop(luaPauseScreen, 1);

	LuaWrapper::CloseLuaState(luaPauseScreen);
}

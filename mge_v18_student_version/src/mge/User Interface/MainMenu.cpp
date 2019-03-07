#include "MainMenu.hpp"

MainMenu::MainMenu(World* world, sf::RenderWindow* window) : world(world)
{

	initialize(window);

	backgroundTexture = new sf::Texture();
	backgroundTexture->loadFromFile("mge\\UI\\MainMenu_background.png");
	BackgroundImage.setTexture(*backgroundTexture);
	BackgroundImage.setPosition(sf::Vector2f(960, 540));
	sf::Vector2u bgSize = backgroundTexture->getSize();
	BackgroundImage.setOrigin(bgSize.x * 0.5f, bgSize.y * 0.5f);
}

MainMenu::~MainMenu()
{
	std::cout << "GC running on:MainMenu.\n";
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(startButton);
	ButtonManager::RemoveButton(exitButton);
	delete startButton;
	delete exitButton;
	delete backgroundTexture;
	//std::cout << "Amount of Buttons: " << ButtonManager::GetAmountOfButtons() << std::endl;
}

void MainMenu::Draw(sf::RenderWindow* window)
{
	window->draw(BackgroundImage);
	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			window->draw(*current->GetSprite());
		}
	}
}

void MainMenu::initialize(sf::RenderWindow* window)
{
	//Mouse setup
	mouse = new GameObject("Mouse");
	mouseBehaviour = new MouseBehaviour(window);
	mouse->setBehaviour(mouseBehaviour);
	world->add(mouse);

	lua_State* luaMainMenu = LuaWrapper::InitializeLuaState("LuaGameScripts/UI/MainMenu.Lua");

	lua_getglobal(luaMainMenu, "Buttons");

	lua_pushnil(luaMainMenu);

	while (lua_next(luaMainMenu, -2) != 0)
	{
		glm::vec3 position = LuaWrapper::GetTableVec3(luaMainMenu, "Position");
		std::string UIType = LuaWrapper::GetTableString(luaMainMenu, "Type");

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaMainMenu, "ButtonType");

			if (ButtonType == "START")
			{
				std::string imagePath = LuaWrapper::GetTableString(luaMainMenu, "ImagePath");
				startButton = new Button(imagePath);
				startButton->SetCommand(new StartCommand());
				startButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(startButton);
			}

			if (ButtonType == "EXIT")
			{
				std::string imagePath = LuaWrapper::GetTableString(luaMainMenu, "ImagePath");
				exitButton = new Button(imagePath);
				exitButton->SetCommand(new ExitCommand(window));
				exitButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(exitButton);
			}
		}
			lua_pop(luaMainMenu, 1);
	}
	lua_pop(luaMainMenu, 1);
}

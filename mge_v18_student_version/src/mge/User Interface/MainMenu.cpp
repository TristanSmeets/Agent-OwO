#include "MainMenu.hpp"

MainMenu::MainMenu(World* world, sf::RenderWindow* window) : world(world)
{
	initialize(window);
}

MainMenu::~MainMenu()
{
	std::cout << "GC running on:MainMenu.\n";
	delete mouseBehaviour;

	world->remove(mouse);
	delete mouse;
	ButtonManager::RemoveButton(startButton);
	ButtonManager::RemoveButton(creditsButton);
	ButtonManager::RemoveButton(exitButton);
	ButtonManager::RemoveButton(controlsButton);
	delete startButton;
	delete creditsButton;
	delete exitButton;
	delete controlsButton;
	delete backgroundTexture;
}

void MainMenu::Draw(sf::RenderWindow* window)
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

void MainMenu::initialize(sf::RenderWindow* window)
{
	lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
	if (AudioLocator::GetAudio()->GetMusicType() != MusicType::MAINMENU)
	{
		AudioLocator::GetAudio()->PlayMusic(LuaWrapper::GetString(luaAudio, "MainMenuBG"));
		AudioLocator::GetAudio()->SetMusicVolume(LuaWrapper::GetNumber<float>(luaAudio, "MainMenuVolume"));
		AudioLocator::GetAudio()->SetMusicPitch(LuaWrapper::GetNumber<float>(luaAudio, "MainMenuPitch"));
		AudioLocator::GetAudio()->SetMusicType(MusicType::MAINMENU);
	}
	LuaWrapper::CloseLuaState(luaAudio);

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
		std::string imagePath = LuaWrapper::GetTableString(luaMainMenu, "ImagePath");

		if (UIType == "BACKGROUND")
		{
			backgroundTexture = new sf::Texture();
			backgroundTexture->loadFromFile(imagePath);
			backgroundImage.setTexture(*backgroundTexture);
			backgroundImage.setPosition(sf::Vector2f(position.x, position.y));
			sf::Vector2u bgSize = backgroundTexture->getSize();
			backgroundImage.setOrigin(bgSize.x * .5f, bgSize.y * .5f);
		}

		if (UIType == "BUTTON")
		{
			std::string ButtonType = LuaWrapper::GetTableString(luaMainMenu, "ButtonType");

			if (ButtonType == "START")
			{
				startButton = new Button(imagePath);
				startButton->SetCommand(new StartCommand());
				startButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(startButton);
			}

			if (ButtonType == "CONTROLS")
			{
				controlsButton = new Button(imagePath);
				controlsButton->SetCommand(new ControlsCommand());
				controlsButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(controlsButton);
			}

			if (ButtonType == "CREDIT")
			{
				creditsButton = new Button(imagePath);
				creditsButton->SetCommand(new CreditsCommand());
				creditsButton->SetPosition(glm::vec2(position.x, position.y));
				ButtonManager::AddButton(creditsButton);
			}

			if (ButtonType == "EXIT")
			{
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


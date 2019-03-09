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
	ButtonManager::RemoveButton(creditsButton);
	ButtonManager::RemoveButton(exitButton);
	delete startButton;
	delete creditsButton;
	delete exitButton;
	delete backgroundTexture;
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

	lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
	bgMusic.openFromFile(LuaWrapper::GetString(luaAudio, "MainMenuBG"));
	bgMusic.setVolume(LuaWrapper::GetNumber<float>(luaAudio, "MainMenuVolume"));
	bgMusic.setPitch(LuaWrapper::GetNumber<float>(luaAudio, "MainMenuPitch"));

	bgMusic.setLoop(true);
	bgMusic.play();

	/*AudioManager::PlayMusic(LuaWrapper::GetString(luaAudio, "BGMainMenu"));
	AudioManager::SetMusicVolume(LuaWrapper::GetNumber<float>(luaAudio, "BGVolume"));
	AudioManager::SetMusicPitch(LuaWrapper::GetNumber<float>(luaAudio, "BGPitch"));
*/

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


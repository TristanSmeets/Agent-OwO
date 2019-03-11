#include "mge/scenes/GameScene.hpp"
#include <iostream>

GameScene::GameScene() : AbstractGame(), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	lua_State * luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
	amountOfLevels = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");
}

GameScene::~GameScene()
{
	std::cout << "GC running on:GameScene\n";
	if (level != nullptr) delete level;
	delete eventQueueBehaviour;
	camera = nullptr;

	if (mainMenu != nullptr)
	{
		delete mainMenu;
		mainMenu = nullptr;
	}
	delete propCreator;

	if (deathScreen != nullptr)
	{
		delete deathScreen;
		deathScreen = nullptr;
	}

	if (pauseScreen != nullptr)
	{
		delete pauseScreen;
		pauseScreen = nullptr;
	}

	if (creditsScreen != nullptr)
	{
		delete creditsScreen;
		creditsScreen = nullptr;
	}
	LuaWrapper::CloseLuaState(config);
	eventQueueBehaviour = nullptr;
	audioManager->StopMusic();
	delete audioManager;
}

void GameScene::initialize()
{
	audioManager = new AudioManager();
	AudioLocator::Provide(audioManager);
	AbstractGame::initialize();
	propCreator = new PropCreator(_world);
	propCreator->LoadProps();
	level = new Level(_world, camera);
}

void GameScene::OnNotify(const GeneralEvent & info)
{
	if (info.startGame)
	{
		delete mainMenu;
		mainMenu = nullptr;
		hud = new HUD(levelNumber);
		propCreator->CreateBGProp(levelNumber);
		level->CreateLevel(levelNumber);
	}
	if (info.resetLevel)
	{
		level->Resetlevel();
		if (deathScreen != nullptr)
		{
			delete deathScreen;
			deathScreen = nullptr;
		}
	}
	if (info.nextLevel)
	{
		if (hud != nullptr)
		{
			delete hud;
			hud = nullptr;
		}
		levelNumber++;
		level->UnloadLevel();
		propCreator->RemoveBGProp();
		if (levelNumber > amountOfLevels)
		{
			levelNumber = 1;
			delete hud;
			hud = nullptr;
			delete level;
			level = nullptr;
			mainMenu = new MainMenu(_world, _window);
		}
		else
		{
			hud = new HUD(levelNumber);
			propCreator->CreateBGProp(levelNumber);
			level->CreateLevel(levelNumber);
		}
	}
	if (info.showGameOver)
		deathScreen = new DeathScreen(_world, _window);
	if (info.showMainMenu)
	{
		levelNumber = 1;
		if (deathScreen != nullptr)
		{
			delete deathScreen;
			deathScreen = nullptr;
		}

		if (hud != nullptr)
		{
			propCreator->RemoveBGProp();
			delete hud;
			hud = nullptr;
		}

		if (pauseScreen != nullptr)
		{
			delete pauseScreen;
			pauseScreen = nullptr;
		}

		if (creditsScreen != nullptr)
		{
			delete creditsScreen;
			creditsScreen = nullptr;
		}

		mainMenu = new MainMenu(_world, _window);
	}
	if (info.showPauseScreen)
		pauseScreen = new PauseScreen(_world, _window);
	if (info.closePauseScreen)
	{
		delete pauseScreen;
		pauseScreen = nullptr;
	}
	if (info.showCreditsScreen)
	{
		delete mainMenu;
		mainMenu = nullptr;
		creditsScreen = new CreditsScreen(_world, _window);
	}
}

void GameScene::_initializeScene()
{
	GameObject* eventQueue = new GameObject("EventQueue");
	eventQueueBehaviour = new QueueBehaviour();
	eventQueue->setBehaviour(eventQueueBehaviour);
	_world->add(eventQueue);

	EventQueue::AddObserver(this);

	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts/config.lua");

	camera = dynamic_cast<Camera*>(CameraFactory(config).CreateGameObject("Camera"));
	_world->add(camera);
	_world->setMainCamera(camera);

	std::cout << "Creating MainMenu.\n";
	mainMenu = new MainMenu(_world, _window);
}

void GameScene::_render()
{
	AbstractGame::_render();

	_window->pushGLStates();

	if (mainMenu != nullptr)
	{
		mainMenu->Draw(_window);
	}

	if (hud != nullptr)
	{
		hud->Draw(_window);
	}

	if (deathScreen != nullptr)
		deathScreen->Draw(_window);

	if (pauseScreen != nullptr)
		pauseScreen->Draw(_window);

	if (creditsScreen != nullptr)
		creditsScreen->Draw(_window);

	_window->popGLStates();
}

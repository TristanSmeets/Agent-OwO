#include "mge/scenes/GameScene.hpp"
#include <iostream>

GameScene::GameScene() : AbstractGame(), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
}

GameScene::~GameScene()
{
	std::cout << "GC running on:GameScene\n";
	delete level;
	delete eventQueueBehaviour;
}

void GameScene::initialize()
{
	AbstractGame::initialize();
}

void GameScene::_initializeScene()
{
	GameObject* eventQueue = new GameObject("EventQueue");
	eventQueueBehaviour = new EventQueueBehaviour();
	eventQueue->setBehaviour(eventQueueBehaviour);
	_world->add(eventQueue);

	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::cout << "Creating Camera\n";
	Camera* camera = dynamic_cast<Camera*>(CameraFactory(config).CreateGameObject("Camera"));
	_world->add(camera);
	_world->setMainCamera(camera);

	std::cout << "Creating the Level\n";
	level = new Level(_world,camera);
	//level->CreateLevel(LuaWrapper::GetNumber<int>(config, "LevelToLoad"));
}

void GameScene::_render()
{
	AbstractGame::_render();
	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			_window->draw(*current->GetSprite());
		}
	}
}


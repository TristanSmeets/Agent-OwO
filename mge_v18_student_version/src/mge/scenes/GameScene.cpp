#include "mge/scenes/GameScene.hpp"
#include "mge/core/Camera.hpp"
#include <iostream>

GameScene::GameScene() : AbstractGame()
{
}

GameScene::~GameScene()
{
	std::cout << "GC running on:GameScene\n";
	delete level;
}

void GameScene::initialize()
{
	AbstractGame::initialize();
}

void GameScene::_initializeScene()
{
	Camera* camera = new Camera("camera", glm::vec3(0,2,0));
	camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::cout << "Creating the Level\n";
	level = new Level(_world);
	level->CreateLevel(LuaWrapper::GetString(config, "LevelToLoad"));
}

void GameScene::_render()
{
	AbstractGame::_render();
}


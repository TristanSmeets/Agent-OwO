#include "mge/scenes/GameScene.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include <iostream>

GameScene::GameScene() : AbstractGame(), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
}

GameScene::~GameScene()
{
	std::cout << "GC running on:GameScene\n";
	delete level;
	delete boxFactory;
}

void GameScene::initialize()
{
	AbstractGame::initialize();
}

void GameScene::_initializeScene()
{
	//Camera* camera = new Camera("camera",
	//	glm::vec3(0.0f,3.0f,5.0f),
	//	glm::perspective(glm::radians(60.0f), 16.0f/9.0f, 0.1f, 1000.0f));
	//////camera->rotate(glm::radians(90.0f), glm::vec3(1, 0, 0));
	//_world->add(camera);
	//_world->setMainCamera(camera);

	boxFactory = new BoxFactory(config);

	/*GameObject* tileObject = boxFactory->CreateGameObject("Tile");
	_world->add(tileObject);
*/
	//camera->setBehaviour(new KeysBehaviour());
	
	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::cout << "Creating the Level\n";
	level = new Level(_world);
	level->CreateLevel(LuaWrapper::GetString(config, "LevelToLoad"));
	level->SetMovableBehaviourStartNodes();
}

void GameScene::_render()
{
	AbstractGame::_render();
}


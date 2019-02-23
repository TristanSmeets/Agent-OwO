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
	std::cout << "Creating the Level\n";
	level = new Level(_world);
	level->CreateLevel(LuaWrapper::GetNumber<int>(config, "LevelToLoad"));
}

void GameScene::_render()
{
	AbstractGame::_render();
}


#include "mge/scenes/GameScene.hpp"
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
	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::cout << "Creating the Level\n";
	level = new Level(_world);
	level->CreateLevel(LuaWrapper::GetString(config, "LevelToLoad"));
}

void GameScene::_render()
{
	AbstractGame::_render();
}


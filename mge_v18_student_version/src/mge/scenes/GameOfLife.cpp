#include <string>
#include "glm.hpp"
//Core
#include "mge/core/Renderer.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
//Materials
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
//Behaviour
#include "mge/behaviours/LuaBehaviour.hpp"

//Util
#include "mge/util/DebugHud.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

#include <lua.hpp>
#include <iostream>

#include "GameOfLife.h"

GameOfLife::GameOfLife():AbstractGame()
{
}

GameOfLife::~GameOfLife()
{
	std::cout << "GC running on:GameOfLife" << std::endl;
	LuaWrapper::CloseLuaState(main);
	delete displayGrid;
	//delete hud;
}

void GameOfLife::initialize()
{
	AbstractGame::initialize();

	//setup the grid.
	displayGrid = new DisplayGrid(_window);
	//hud = new DebugHud(_window);
}

void GameOfLife::_initializeScene()
{
	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("camera", glm::vec3(0, 0, 15));
	_world->add(camera);
	_world->setMainCamera(camera);


	std::cout << "Creating GameObject" << std::endl;
	GameObject* luaObject = new GameObject("LuaObject");
	main = LuaWrapper::InitializeLuaState("LuaGameScripts\\Main.lua");
	std::cout << "Setting LuaBehaviour with luaState: " << main << std::endl;
	luaObject->setBehaviour(new LuaBehaviour(main));
	_world->add(luaObject);
}

void GameOfLife::_render()
{
	AbstractGame::_render();
	displayGrid->Draw();
	lua_getglobal(main, "Draw");
	lua_call(main, 0, 0);

	//updateHud();
}

void GameOfLife::updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	hud->setDebugInfo(debugInfo);
	hud->draw();
}

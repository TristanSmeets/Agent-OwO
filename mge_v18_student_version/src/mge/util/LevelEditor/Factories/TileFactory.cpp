#include "mge/util/LevelEditor/Factories/TileFactory.hpp"

//For printing debug info
#include <iostream>

TileFactory::TileFactory(lua_State* config)
{
	std::string tileFile = LuaWrapper::GetString(config, "Tile");
	lua_State* luaTile = LuaWrapper::InitializeLuaState(tileFile);
	
	std::cout << "Loading Tile Mesh\n";
	mesh = getMesh(luaTile);
	std::cout << "Loading Tile TextureMaterial\n";
	material = getTextureMaterial(luaTile);
	behaviour = new NullBehaviour();
	LuaWrapper::CloseLuaState(luaTile);
}


TileFactory::~TileFactory()
{
	std::cout << "GC running on:TileFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject * TileFactory::CreateGameObject(const std::string & name)
{
	GameObject* newGameObject = new GameObject(name);
	addMesh(newGameObject);
	addMaterial(newGameObject);
	addBehaviour(newGameObject);
	return newGameObject;
}

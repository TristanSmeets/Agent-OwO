#include "mge/util/LevelEditor/Factories/TileFactory.hpp"

//For printing debug info
#include <iostream>

TileFactory::TileFactory() : AbstractFactory()
{
}

TileFactory::TileFactory(lua_State* config) : AbstractFactory()
{
	std::string tileFile = LuaWrapper::GetString(config, "Tile");
	luaTile = LuaWrapper::InitializeLuaState(tileFile);
	
	std::cout << "Loading Tile Mesh\n";
	mesh = getMesh(luaTile);
	std::cout << "Loading Tile TextureMaterial\n";
	material = getTextureMaterial(luaTile);
	behaviour = new NullBehaviour();
	
}


TileFactory::~TileFactory()
{
	AbstractFactory::~AbstractFactory();
	std::cout << "GC running on:TileFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
	LuaWrapper::CloseLuaState(luaTile);
}

GameObject* TileFactory::CreateGameObject(const std::string& name)
{
	std::cout << "Creating " << name << std::endl;
	TileObject* newTileObject = new TileObject(luaTile, name);
	addMesh(newTileObject);
	addMaterial(newTileObject);
	addBehaviour(newTileObject);
	return newTileObject;
}

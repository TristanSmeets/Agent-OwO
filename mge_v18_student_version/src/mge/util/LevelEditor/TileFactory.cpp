#include "mge/util/LevelEditor/TileFactory.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/behaviours/NullBehaviour.hpp"

//For printing debug info
#include <iostream>

TileFactory::TileFactory()
{
	//Opening config lua file to get path to the tile lua file.
	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::string tileFile = LuaWrapper::GetString(config, "Tile");
	LuaWrapper::CloseLuaState(config);
	lua_State* luaTile = LuaWrapper::InitializeLuaState(tileFile);
	
	std::cout << "Loading Tile Mesh\n";
	mesh = Mesh::load(LuaWrapper::GetString(luaTile, "Mesh"));
	std::cout << "Loading Tile TextureMaterial";
	material = new TextureMaterial(Texture::load(LuaWrapper::GetString(luaTile, "Texture")));
	behaviour = new NullBehaviour();
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
	GameObject* newGameObject = new GameObject(name, glm::vec3(0, 0, 0));
	addMesh(newGameObject);
	addMaterial(newGameObject);
	addBehaviour(newGameObject);
	return newGameObject;
}

void TileFactory::addMesh(GameObject * gameObject)
{
	gameObject->setMesh(mesh);
}

void TileFactory::addMaterial(GameObject * gameObject)
{
	gameObject->setMaterial(material);
}

void TileFactory::addBehaviour(GameObject * gameObject)
{
	gameObject->setBehaviour(behaviour);
}


#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"
#include "mge/gameplay/GameObjects/TileObject.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class TileFactory :
	public AbstractFactory
{
public:
	TileFactory();
	TileFactory(lua_State* config);
	virtual ~TileFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	lua_State* luaTile;
	/*void addMesh(GameObject* gameObject);
	void addMaterial(GameObject* gameObject);
	void addBehaviour(GameObject* gameObject);*/
};
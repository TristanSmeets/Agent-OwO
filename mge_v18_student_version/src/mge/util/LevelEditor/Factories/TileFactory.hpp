#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class TileFactory :
	public AbstractFactory
{
public:
	TileFactory();
	TileFactory(lua_State* config);
	virtual ~TileFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	/*void addMesh(GameObject* gameObject);
	void addMaterial(GameObject* gameObject);
	void addBehaviour(GameObject* gameObject);*/
};
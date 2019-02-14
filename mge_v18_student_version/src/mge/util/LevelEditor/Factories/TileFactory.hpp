#pragma once

#include "mge/core/AbstractFactory.hpp"

class TileFactory :
	public AbstractFactory
{
public:
	TileFactory(lua_State* config);
	~TileFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	/*void addMesh(GameObject* gameObject);
	void addMaterial(GameObject* gameObject);
	void addBehaviour(GameObject* gameObject);*/
};
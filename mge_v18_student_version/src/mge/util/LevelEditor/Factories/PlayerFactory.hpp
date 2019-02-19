#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class Node;

class PlayerFactory :
	public AbstractFactory
{
public:
	PlayerFactory();
	PlayerFactory(lua_State* config);
	virtual ~PlayerFactory();
	GameObject* CreateGameObject(const std::string& name);
	GameObject* CreateGameObjectWithNode(const std::string& name, Node* node);
};
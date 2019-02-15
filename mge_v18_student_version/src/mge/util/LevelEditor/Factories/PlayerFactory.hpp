#pragma once

#include "mge/core/AbstractFactory.hpp"

class PlayerFactory :
	public AbstractFactory
{
public:
	PlayerFactory(lua_State* config);
	virtual ~PlayerFactory();
	GameObject* CreateGameObject(const std::string& name);
};
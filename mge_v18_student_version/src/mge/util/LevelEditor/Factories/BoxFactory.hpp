#pragma once

#include "mge/core/AbstractFactory.hpp"

class BoxFactory : 
	public AbstractFactory
{
public:
	BoxFactory(lua_State* config);
	~BoxFactory();
	GameObject* CreateGameObject(const std::string& name);
};

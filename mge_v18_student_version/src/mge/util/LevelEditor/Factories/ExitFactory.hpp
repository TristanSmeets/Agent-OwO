#pragma once

#include "mge/core/AbstractFactory.hpp"

class ExitFactory :
	public AbstractFactory
{
public:
	ExitFactory(lua_State* config);
	~ExitFactory();
	GameObject* CreateGameObject(const std::string& name);
};
#pragma once

#include "mge/core/AbstractFactory.hpp"

class SwitchFactory :
	public AbstractFactory
{
public:
	SwitchFactory(lua_State* config);
	virtual ~SwitchFactory();
	GameObject* CreateGameObject(const std::string& name);
};
#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class SwitchFactory :
	public AbstractFactory
{
public:
	SwitchFactory();
	SwitchFactory(lua_State* config);
	virtual ~SwitchFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	lua_State* luaSwitch;
};
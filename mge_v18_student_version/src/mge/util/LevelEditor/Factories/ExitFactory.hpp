#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class ExitFactory :
	public AbstractFactory
{
public:
	ExitFactory();
	ExitFactory(lua_State* config);
	~ExitFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	lua_State* luaExit;
};
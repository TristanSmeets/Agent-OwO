#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

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
	lua_State* luaLevelInfo;
	unsigned int switches;
	unsigned int levelNumber = 1;
};
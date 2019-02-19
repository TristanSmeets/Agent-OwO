#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class StartFactory : public AbstractFactory
{
public:
	StartFactory();
	StartFactory(lua_State* config);
	~StartFactory();
	GameObject* CreateGameObject(const std::string& name);
private:
	lua_State* luaStart;
};

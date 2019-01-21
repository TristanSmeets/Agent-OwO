#include "mge/behaviours/LuaBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>
#include "mge/util/LuaWrapper.hpp"

LuaBehaviour::LuaBehaviour(lua_State* luaState) : AbstractBehaviour(), main(luaState)
{
	//Construction of things goes here
	lua_getglobal(main, "Start");
	lua_call(main, 0, 0);
}

LuaBehaviour::~LuaBehaviour()
{
	LuaWrapper::CloseLuaState(main);
}

void LuaBehaviour::update( float pStep )
{
	lua_getglobal(main, "Update");
	lua_call(main, 0, 0);
}


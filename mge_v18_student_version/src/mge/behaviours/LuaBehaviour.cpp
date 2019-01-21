#include "mge/behaviours/LuaBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>
#include "mge/util/LuaWrapper.hpp"
#include <lua.hpp>

LuaBehaviour::LuaBehaviour(lua_State* luaState) : AbstractBehaviour(), main(luaState)
{
	//Construction of things goes here
	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	int screenWidth = LuaWrapper::GetNumber<int>(config, "ScreenWidth");
	int screenHeight = LuaWrapper::GetNumber<int>(config, "ScreenHeight");
	int SquareSize = LuaWrapper::GetNumber<int>(config, "SquareSize");
	LuaWrapper::CloseLuaState(config);

	lua_getglobal(main, "Start");
	lua_pushinteger(main, screenWidth);
	lua_pushinteger(main, screenHeight);
	lua_pushinteger(main, SquareSize);
	lua_call(main, 3, 0);
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


#include "mge/behaviours/LuaBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>
#include "mge/util/LuaWrapper.hpp"
#include <lua.hpp>
#include "mge/util/DrawRectangle.hpp"

LuaBehaviour::LuaBehaviour(lua_State* luaState) : AbstractBehaviour(), main(luaState)
{
	//Initializing the DrawRectangle UserData
	DrawRectangle::InitializeLua(main);

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
	int status = lua_pcall(main, 3, 0, 0);
	if (status)
		std::cout << "Lua Error: " << std::to_string(status) << "\n" << lua_tostring(main, -1) << "\nStack: " << lua_gettop(main) << std::endl;
}

LuaBehaviour::~LuaBehaviour()
{
	LuaWrapper::CloseLuaState(main);
}

void LuaBehaviour::update( float pStep )
{
	lua_getglobal(main, "Update");
	lua_pcall(main, 0, 0, 0);
}


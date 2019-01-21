#include <iostream>
#include <lua.hpp>
#include <stdexcept>
#include "LuaWrapper.hpp"

lua_State* LuaWrapper::InitializeLuaState(const std::string& filePath)
{
	std::cout << "Initializing lua_State..." << std::endl;
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	std::cout << "Loading file: " << filePath << std::endl;
	std::cout << filePath <<" at: " << lua << std::endl;
	luaL_loadfile(lua, filePath.c_str());
	lua_call(lua, 0, 0);
	std::cout << filePath << " initialized at: " << lua <<std::endl;
	return lua;
}

std::string LuaWrapper::GetString(lua_State* luaState, const std::string& variableName)
{
	lua_getglobal(luaState, variableName.c_str());
	if (lua_isstring(luaState, -1))
	{
		std::string text = lua_tostring(luaState, -1);
		lua_pop(luaState, 1);
		return text;
	}
	else
		throw std::invalid_argument("variable isn't a string");
}

void LuaWrapper::CloseLuaState(lua_State * luaState)
{
	std::cout << "Closing lua_State at " << luaState << std::endl;
	lua_close(luaState);
}

#include <iostream>
#include <lua.hpp>
#include <stdexcept>
#include "LuaWrapper.hpp"

lua_State* LuaWrapper::InitializeLuaState(const std::string& filePath)
{
	std::cout << "Initializing lua_State..." << std::endl;
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_loadfile(lua, filePath.c_str());
	lua_call(lua, 0, 0);
	std::cout << "lua_State initialized..." << std::endl;
	return lua;
}

std::string LuaWrapper::GetString(lua_State* luaState, const std::string& variableName)
{
	lua_getglobal(luaState, variableName.c_str());
	if (lua_isstring(luaState, -1))
		return std::string(lua_tostring(luaState, -1));
	else
		throw std::invalid_argument("variable isn't a string");
}

void LuaWrapper::CloseLuaState(lua_State * luaState)
{
	std::cout << "Closing lua_State..." << std::endl;
	lua_close(luaState);
}

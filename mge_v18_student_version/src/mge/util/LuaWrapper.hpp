#ifndef LUAWRAPPER_HPP
#define LUAWRAPPER_HPP

#include <lua.hpp>
#include <string>

class LuaWrapper
{
public:
	//Creates a new lua_State and initializes all the variables and functions
	static lua_State* InitializeLuaState(const std::string& filePath);
	
	//Numbers
	//Returns the number variable. If the variable isn't a number throw's an exception.
	static float GetNumberF(lua_State* luaState, const std::string& variableName);
	//Returns the number variable. If the variable isn't a number throw's an exception.
	static int GetNumberI(lua_State* luaState, const std::string& variableName);

	//Strings
	//Returns the string variable. if the variable isn't a string throw's an exception.
	static std::string GetString(lua_State* luaState, const std::string& variableName);

	//Freeing Lua
	//Closes a lua_State
	static void CloseLuaState(lua_State* luaState);
};
#endif // !LUAWRAPPER_HPP

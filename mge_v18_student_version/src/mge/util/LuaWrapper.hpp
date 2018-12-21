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
	template <typename T> static T GetNumber(lua_State* luaState, const std::string& variableName)
	{
		lua_getglobal(luaState, variableName.c_str());
		if (lua_isnumber(luaState, -1))
			return (T)lua_tonumber(luaState, -1);
		else
			throw std::invalid_argument("variable isn't a number");
	}

	//Strings
	//Returns the string variable. if the variable isn't a string throw's an exception.
	static std::string GetString(lua_State* luaState, const std::string& variableName);

	//Freeing Lua
	//Closes a lua_State
	static void CloseLuaState(lua_State* luaState);
};
#endif // !LUAWRAPPER_HPP

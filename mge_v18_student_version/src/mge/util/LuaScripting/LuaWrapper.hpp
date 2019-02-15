#ifndef LUAWRAPPER_HPP
#define LUAWRAPPER_HPP

#include <lua.hpp>
#include <string>
#include "glm.hpp"

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
		{
			T number = (T)lua_tonumber(luaState, -1);
			lua_pop(luaState, 1);
			return number;
		}
		else
			throw std::invalid_argument("variable isn't a number");
	}

	template <typename T> static T GetNumber(lua_State* luaState)
	{
		if (lua_isnumber(luaState, -1))
		{
			T number = (T)lua_tonumber(luaState, -1);
			lua_pop(luaState, 1);
			return number;
		}
		else
			throw std::invalid_argument("Is not a valid argument");
	}

	//Strings
	//Returns the string variable. if the variable isn't a string throw's an exception.
	static std::string GetString(lua_State* luaState, const std::string& variableName);

	//Table
	//Returns the value that belongs to the passed in key. 
	//Checks what the value inside the table is and returns that type. 
	template <typename T> static T GetTableValue(lua_State* luaState, const std::string& tableName, const std::string& key)
	{
		//Set the table to the top of the stack
		lua_getglobal(luaState, tableName.c_str());

		//Put the key on the stack.
		lua_pushstring(luaState, key.c_str());
		//Gets the value from the table.
		lua_gettable(luaState, -2);
		T value;

		if (lua_isnumber(luaState, -1))
			value = (T)lua_tonumber(luaState, -1);
		else if (lua_isboolean(luaState, -1))
			value = (T)lua_toboolean(luaState, -1);

		lua_pop(luaState, 1);
		return value;
	}
	static std::string GetTableString(lua_State* luaState, const std::string& key);
	static double GetTableNumber(lua_State* luaState, const std::string& key);
	static glm::vec3 GetTableVec3(lua_State* luaState, const std::string& key);
	static glm::vec4 GetTableVec4(lua_State* luaState, const std::string& key);
	static glm::quat GetTableQuat(lua_State* luaState, const std::string& key);
	//Freeing Lua
	//Closes a lua_State
	static void CloseLuaState(lua_State* luaState);
};
#endif // !LUAWRAPPER_HPP

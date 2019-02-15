#include <iostream>
#include <lua.hpp>
#include <stdexcept>
#include "LuaWrapper.hpp"

lua_State* LuaWrapper::InitializeLuaState(const std::string& filePath)
{
	//std::cout << "Initializing lua_State..." << std::endl;
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);
	std::cout << "Initializing Lua file: " << filePath << std::endl;
	//std::cout << filePath <<" at: " << lua << std::endl;
	luaL_loadfile(lua, filePath.c_str());
	std::cout << filePath << " initialized at: " << lua <<std::endl;
	int status = lua_pcall(lua, 0, 0, 0, 0);
	if (status)
		std::cout << "Lua Error: " << std::to_string(status) << "\n" << lua_tostring(lua, -1) << "\nStack: " << lua_gettop(lua) << std::endl;
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

std::string LuaWrapper::GetTableString(lua_State * luaState, const std::string& key)
{
	lua_pushstring(luaState, key.c_str());
	lua_gettable(luaState, -2);

	std::string value;

	if (lua_isstring(luaState, -1))
		value = lua_tostring(luaState, -1);
	else
		throw std::invalid_argument("Not a string.");

	lua_pop(luaState, 1);
	return value;
}

double LuaWrapper::GetTableNumber(lua_State * luaState, const std::string& key)
{
	lua_pushstring(luaState, key.c_str());

	lua_gettable(luaState, -2);
	double value;

	if (lua_isnumber(luaState, -1))
		value = lua_tonumber(luaState, -1);
	else
		throw std::invalid_argument("variable isn't a number");
	
	lua_pop(luaState, 1);

	return value;
}

glm::vec3 LuaWrapper::GetTableVec3(lua_State * luaState, const std::string & key)
{
	//Pushing value on stack
	lua_pushstring(luaState, key.c_str());
	//Putting key value on stack
	lua_gettable(luaState, -2);
	glm::vec3 vector3;
	if (lua_istable(luaState, -1))
	{
		vector3 = glm::vec3(
			LuaWrapper::GetTableNumber(luaState, "x"),
			LuaWrapper::GetTableNumber(luaState, "y"),
			LuaWrapper::GetTableNumber(luaState, "z"));
	}
	else
		throw std::invalid_argument("Not a table.");
	lua_pop(luaState, 1);
	return vector3;
}

glm::vec4 LuaWrapper::GetTableVec4(lua_State * luaState, const std::string & key)
{
	//Pushing value on stack
	lua_pushstring(luaState, key.c_str());
	//Putting key value on stack
	lua_gettable(luaState, -2);
	glm::vec4 vector4;
	if (lua_istable(luaState, -1))
	{
		vector4 = glm::vec4(
			LuaWrapper::GetTableNumber(luaState, "x"),
			LuaWrapper::GetTableNumber(luaState, "y"),
			LuaWrapper::GetTableNumber(luaState, "z"),
			LuaWrapper::GetTableNumber(luaState, "w"));
	}
	else
		throw std::invalid_argument("Not a table.");
	lua_pop(luaState, 1);
	return glm::vec4();
}

glm::quat LuaWrapper::GetTableQuat(lua_State * luaState, const std::string & key)
{
	//Pushing value on stack
	lua_pushstring(luaState, key.c_str());
	//Putting key value on stack
	lua_gettable(luaState, -2);

	glm::quat rotation;
	if (lua_istable(luaState, -1))
	{
		rotation = glm::quat(
			LuaWrapper::GetTableNumber(luaState, "w"),
			LuaWrapper::GetTableNumber(luaState, "x"),
			LuaWrapper::GetTableNumber(luaState, "y"),
			LuaWrapper::GetTableNumber(luaState, "z"));
	}
	else
		throw std::invalid_argument("Not a table.");
	lua_pop(luaState, 1);
	return rotation;
}

void LuaWrapper::CloseLuaState(lua_State * luaState)
{
	std::cout << "Closing lua_State at " << luaState << std::endl;
	lua_close(luaState);
}

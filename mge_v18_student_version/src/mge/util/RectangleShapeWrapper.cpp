#include "mge/util/RectangleShapeWrapper.hpp"
#include "mge/util/DisplayGrid.h"
#include <iostream>
#include <new>

#define TRISTAN_LUA_VARIABLE_NAME "RectangleShape"
#define TRISTAN_LUA_METATABLE "meta.RectangleShape"
#define TRISTAN_LUA_INDEX "__index"
#define TRISTAN_LUA_FILEPATH "LuaGameScripts\\Main.lua"
#define TRISTAN_LUA_COLOUR "Colour"

RectangleShapeWrapper::RectangleShapeWrapper()
{
	rectangle = new sf::RectangleShape();
	rectangle->setFillColor(sf::Color::Yellow);
	DisplayGrid::AddRectangleShape(this);
}

RectangleShapeWrapper::~RectangleShapeWrapper()
{
	std::cout << "GC running on:RectangleShapeWrapper" << std::endl;
	delete rectangle;
}

static const struct luaL_Reg MetaLib[] =
{
	{"SetColour", RectangleShapeWrapper::luaSetColour},
	{"SetPosition", RectangleShapeWrapper::luaSetPosition},
	{"SetSquareSize", RectangleShapeWrapper::luaSetSquareSize},
	
	{NULL, NULL}
};

static const struct luaL_Reg DrawRectangleLib[] =
{
	{"New", RectangleShapeWrapper::luaNewRectangleShapeWrapper},
	{NULL, NULL}
};

void RectangleShapeWrapper::SetPosition(float xValue, float yValue)
{
	rectangle->setPosition(xValue, yValue);
}

void RectangleShapeWrapper::SetSquareSize(float size)
{
	rectangle->setSize(sf::Vector2f(size, size));
}

void RectangleShapeWrapper::SetColour(float r, float g, float b, float a)
{
	rectangle->setFillColor(sf::Color(
		std::ceil(r * 255),
		std::ceil(g * 255),
		std::ceil(b * 255),
		std::ceil(a * 255)));
}

sf::RectangleShape& RectangleShapeWrapper::GetRectangleShape()
{
	return (*rectangle);
}

int RectangleShapeWrapper::luaNewRectangleShapeWrapper(lua_State * lua)
{
	size_t nBytes = sizeof(RectangleShapeWrapper);
	RectangleShapeWrapper* drawRectangle = static_cast<RectangleShapeWrapper*>(lua_newuserdata(lua, nBytes));

	new (drawRectangle) RectangleShapeWrapper();

	luaL_getmetatable(lua, TRISTAN_LUA_METATABLE);
	lua_setmetatable(lua, -2);
	return 1;
}

int RectangleShapeWrapper::luaSetPosition(lua_State *lua)
{
	RectangleShapeWrapper* drawRectangle = static_cast<RectangleShapeWrapper*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));
	
	float x = lua_tonumber(lua, 2);
	float y = lua_tonumber(lua, 3);

	drawRectangle->SetPosition(x, y);
	return 0;
}

int RectangleShapeWrapper::luaSetColour(lua_State *lua)
{
	RectangleShapeWrapper* rectangle = static_cast<RectangleShapeWrapper*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));

	float red = lua_tonumber(lua, 2);
	float green = lua_tonumber(lua, 3);
	float blue = lua_tonumber(lua, 4);
	float alpha = lua_tonumber(lua, 5);

	rectangle->SetColour(red, green, blue, alpha);

	return 0;
}

int RectangleShapeWrapper::luaSetSquareSize(lua_State* lua)
{
	RectangleShapeWrapper* rectangle = static_cast<RectangleShapeWrapper*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));

	float squareSize = lua_tonumber(lua, 2);
	rectangle->SetSquareSize(squareSize);

	return 0;
}

void RectangleShapeWrapper::InitializeLua(lua_State* lua)
{	
	luaL_openlibs(lua);

	//Creating new metatable and puts it on the lua stack at -1
	luaL_newmetatable(lua, TRISTAN_LUA_METATABLE);

	//Pushing string: __index onto stack. __index at -1. metatable at -2
	lua_pushstring(lua, TRISTAN_LUA_INDEX);

	//Pushing a copy of the metatable to the top of the stack.
	lua_pushvalue(lua, -2);
	
	//Setting table on stack
	lua_settable(lua, -3);

	//Setting metatable functions
	luaL_setfuncs(lua, MetaLib, 0);
	
	//Setting the metatable
	luaL_newlib(lua, DrawRectangleLib);
	luaL_getmetatable(lua, TRISTAN_LUA_METATABLE);
	lua_setmetatable(lua, -2);
	lua_setglobal(lua, TRISTAN_LUA_VARIABLE_NAME);

	luaL_loadfile(lua, TRISTAN_LUA_FILEPATH);
	lua_pcall(lua, 0, 0, 0);
}


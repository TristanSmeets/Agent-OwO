#include "mge/util/DrawRectangle.hpp"
#include "mge/util/DisplayGrid.h"
#include <iostream>
#include <new>

#define TRISTAN_LUA_VARIABLE_NAME "DrawRectangle"
#define TRISTAN_LUA_METATABLE "meta.DrawRectangle"
#define TRISTAN_LUA_INDEX "__index"
#define TRISTAN_LUA_FILEPATH "LuaGameScripts\\Main.lua"
#define TRISTAN_LUA_COLOUR "Colour"

DrawRectangle::DrawRectangle()
{
	rectangle = new sf::RectangleShape();
	rectangle->setFillColor(sf::Color::Yellow);
	DisplayGrid::AddDrawRectangle(this);
}

DrawRectangle::~DrawRectangle()
{
	delete rectangle;
}

static const struct luaL_Reg MetaLib[] =
{
	{"SetColour", DrawRectangle::luaSetColour},
	{"SetPosition", DrawRectangle::luaSetPosition},
	{"SetSquareSize", DrawRectangle::luaSetSquareSize},
	
	{NULL, NULL}
};

static const struct luaL_Reg DrawRectangleLib[] =
{
	{"New", DrawRectangle::luaNewDrawRectangle},
	{NULL, NULL}
};

void DrawRectangle::SetPosition(float xValue, float yValue)
{
	rectangle->setPosition(xValue, yValue);
}

void DrawRectangle::SetSquareSize(float size)
{
	rectangle->setSize(sf::Vector2f(size, size));
}

void DrawRectangle::SetColour(float r, float g, float b, float a)
{
	rectangle->setFillColor(sf::Color(
		std::ceil(r * 255),
		std::ceil(g * 255),
		std::ceil(b * 255),
		std::ceil(a * 255)));
}

sf::RectangleShape& DrawRectangle::GetRectangleShape()
{
	return (*rectangle);
}

int DrawRectangle::luaNewDrawRectangle(lua_State * lua)
{
	size_t nBytes = sizeof(DrawRectangle);
	DrawRectangle* drawRectangle = static_cast<DrawRectangle*>(lua_newuserdata(lua, nBytes));

	new (drawRectangle) DrawRectangle();

	luaL_getmetatable(lua, TRISTAN_LUA_METATABLE);
	lua_setmetatable(lua, -2);
	return 1;
}

int DrawRectangle::luaSetPosition(lua_State *lua)
{
	DrawRectangle* drawRectangle = static_cast<DrawRectangle*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));
	
	float x = lua_tonumber(lua, 2);
	float y = lua_tonumber(lua, 3);

	drawRectangle->SetPosition(x, y);
	return 0;
}

int DrawRectangle::luaSetColour(lua_State *lua)
{
	DrawRectangle* rectangle = static_cast<DrawRectangle*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));

	float red = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "r");
	float green = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "g");
	float blue = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "b");
	float alpha = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "a");

	rectangle->SetColour(red, green, blue, alpha);

	return 0;
}

int DrawRectangle::luaSetSquareSize(lua_State* lua)
{
	DrawRectangle* rectangle = static_cast<DrawRectangle*>(luaL_checkudata(lua, 1, TRISTAN_LUA_METATABLE));

	float squareSize = lua_tonumber(lua, 2);
	rectangle->SetSquareSize(squareSize);

	return 0;
}

void DrawRectangle::InitializeLua(lua_State* lua)
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


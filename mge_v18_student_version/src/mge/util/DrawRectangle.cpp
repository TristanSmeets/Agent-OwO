#include "mge/util/DrawRectangle.hpp"
#include "mge/util/DisplayGrid.h"
#include <iostream>

#define TRISTAN_LUA_VARIABLE_NAME "DrawRectangle"
#define TRISTAN_LUA_METATABLE "meta.DrawRectangle"
#define TRISTAN_LUA_INDEX "__index"
#define TRISTAN_LUA_FILEPATH "LuaGameScripts\\Main.lua"
#define TRISTAN_LUA_COLOUR "Colour"

DrawRectangle::DrawRectangle()
{
	rectangle = new sf::RectangleShape();
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
	{"UpdateRectangle", DrawRectangle::luaUpdateRectangle},
	{NULL, NULL}
};

static const struct luaL_Reg DrawRectangleLib[] =
{
	{"New", DrawRectangle::luaNewDrawRectangle},
	{NULL, NULL}
};

void DrawRectangle::SetXY(float xValue, float yValue)
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
	DrawRectangle* rectangle;
	//float x = LuaWrapper::GetNumber<float>(lua);
	//float y = LuaWrapper::GetNumber<float>(lua);
	//int squareSize = LuaWrapper::GetNumber<int>(lua);
	
	//Getting RGBA values from the table.
	/*float red = LuaWrapper::GetTableValue<float>(lua, "Colour", "r");
	float green = LuaWrapper::GetTableValue<float>(lua, "Colour", "g");
	float blue = LuaWrapper::GetTableValue<float>(lua, "Colour", "b");
	float alpha = LuaWrapper::GetTableValue<float>(lua, "Colour", "a");*/

	size_t nBytes = sizeof(DrawRectangle*);
	rectangle = static_cast<DrawRectangle*>(lua_newuserdata(lua, nBytes));
	//std::cout << "Na static_cast Rectangle: " << rectangle << std::endl;

	//std::cout << "X,Y,SquareSize: " << x << " " << y << " " << squareSize << std::endl;

	//rectangle->GetRectangleShape().setPosition(x, y);
	//rectangle->SetXY(x, y);
	//rectangle->SetSquareSize(squareSize);
	//rectangle->SetColour(red, green, blue, alpha);
	return 1;
}

int DrawRectangle::luaUpdateRectangle(lua_State * lua)
{
	DrawRectangle* rectangle;
	if (luaL_checkudata(lua, 1, TRISTAN_LUA_VARIABLE_NAME))
	{
		rectangle = static_cast<DrawRectangle*>(lua_touserdata(lua, 1));
	}
	if (rectangle != nullptr)
	{
		float red = LuaWrapper::GetTableValue<float>(lua, "colour", "r");
		float green = LuaWrapper::GetTableValue<float>(lua, "colour", "g");
		float blue = LuaWrapper::GetTableValue<float>(lua, "colour", "b");
		float alpha = LuaWrapper::GetTableValue<float>(lua, "colour", "a");
		rectangle->SetColour(red, green, blue, alpha);
	}
	return 0;
}

int DrawRectangle::luaSetPosition(lua_State *lua)
{
	DrawRectangle* rectangle;

	if (luaL_checkudata(lua, 1, TRISTAN_LUA_VARIABLE_NAME))
		rectangle = static_cast<DrawRectangle*>(lua_touserdata(lua, 1));
	if (rectangle != nullptr)
	{
		float x = LuaWrapper::GetNumber<float>(lua);
		float y = LuaWrapper::GetNumber<float>(lua);
		rectangle->SetXY(x, y);
	}
	return 0;
}

int DrawRectangle::luaSetColour(lua_State *lua)
{
	DrawRectangle* rectangle;

	if (luaL_checkudata(lua, 1, TRISTAN_LUA_VARIABLE_NAME))
		rectangle = static_cast<DrawRectangle*>(lua_touserdata(lua, 1));
	if (rectangle != nullptr)
	{
		float red = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "r");
		float green = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "g");
		float blue = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "b");
		float alpha = LuaWrapper::GetTableValue<float>(lua, TRISTAN_LUA_COLOUR, "a");

		rectangle->SetColour(red, green, blue, alpha);
	}
	return 0;
}

int DrawRectangle::luaSetSquareSize(lua_State* lua)
{
	DrawRectangle* rectangle;

	if (luaL_checkudata(lua, 1, TRISTAN_LUA_VARIABLE_NAME))
		rectangle = static_cast<DrawRectangle*>(lua_touserdata(lua, 1));
	if (rectangle != nullptr)
	{
		float squareSize = LuaWrapper::GetNumber<float>(lua);

		rectangle->SetSquareSize(squareSize);
	}
	return 0;
}

void DrawRectangle::InitializeLua(lua_State* lua)
{	
	luaL_openlibs(lua);

	//Creating new metatable.
	luaL_newmetatable(lua, TRISTAN_LUA_METATABLE);

	//Pushing string: __index onto stack
	lua_pushstring(lua, TRISTAN_LUA_INDEX);

	//Pushing metatable to stack
	lua_pushvalue(lua, -2);
	
	//Setting metatable
	lua_settable(lua, -3);

	//Setting metatable functions
	luaL_setfuncs(lua, MetaLib, 0);
	
	//Setting the metatable
	luaL_newlib(lua, DrawRectangleLib);
	luaL_getmetatable(lua, TRISTAN_LUA_METATABLE);

	lua_setmetatable(lua, -2);
	lua_setglobal(lua, TRISTAN_LUA_VARIABLE_NAME);

	std::cout << "Loading file: " << TRISTAN_LUA_FILEPATH <<  std::endl;
	luaL_loadfile(lua, TRISTAN_LUA_FILEPATH);
	lua_pcall(lua, 0, 0,0);
}


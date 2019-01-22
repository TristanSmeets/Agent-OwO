#include "mge/util/DrawRectangle.hpp"
#include "mge/util/DisplayGrid.h"
#include <iostream>

DrawRectangle::DrawRectangle()
{
	rectangle = new sf::RectangleShape();
	DisplayGrid::AddDrawRectangle(this);
}

DrawRectangle::~DrawRectangle()
{
	delete rectangle;
}

static const struct luaL_Reg DrawRectangleMetaLib[] =
{
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
	float x = LuaWrapper::GetNumber<float>(lua);
	float y = LuaWrapper::GetNumber<float>(lua);
	int squareSize = LuaWrapper::GetNumber<int>(lua);
	
	//Getting RGBA values from the table.
	float red = LuaWrapper::GetTableValue<float>(lua, "Colour", "r");
	float green = LuaWrapper::GetTableValue<float>(lua, "Colour", "g");
	float blue = LuaWrapper::GetTableValue<float>(lua, "Colour", "b");
	float alpha = LuaWrapper::GetTableValue<float>(lua, "Colour", "a");

	size_t nBytes = sizeof(DrawRectangle);
	rectangle = static_cast<DrawRectangle*>(lua_newuserdata(lua, nBytes));
	rectangle->SetXY(x, y);
	rectangle->SetSquareSize(squareSize);
	//rectangle->SetColour(red, green, blue, alpha);
	return 1;
}

int DrawRectangle::luaUpdateRectangle(lua_State * lua)
{
	DrawRectangle* rectangle;
	if (luaL_checkudata(lua, 1, "drawRectangle"))
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

void DrawRectangle::InitializeLua()
{
	std::string drawRectangleMeta = "drawRectangleMeta";
	std::string GlobalDrawRectangle = "DrawRectangle";
	std::string index = "__index";
	std::string filepath = "LuaGameScripts\\BaseOrganism.lua";

	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);

	std::cout << "Creating new metatable." << std::endl;
	luaL_newmetatable(lua, drawRectangleMeta.c_str());

	std::cout << "Pushing string: __index onto stack" << std::endl;
	lua_pushstring(lua, index.c_str());
	
	std::cout << "Pushing metatable to stack" << std::endl;
	lua_pushvalue(lua, -2); //Pushes the metatable
	
	std::cout << "Setting metatable" << std::endl;
	lua_settable(lua, -3);

	luaL_setfuncs(lua, DrawRectangleMetaLib, 0);
	
	luaL_newlib(lua, DrawRectangleLib);
	luaL_getmetatable(lua, drawRectangleMeta.c_str());

	lua_setmetatable(lua, -2);
	lua_setglobal(lua, GlobalDrawRectangle.c_str());

	std::cout << "Loading file: " << filepath <<  std::endl;
	luaL_loadfile(lua, filepath.c_str());
	lua_pcall(lua, 0, 0,0);
}


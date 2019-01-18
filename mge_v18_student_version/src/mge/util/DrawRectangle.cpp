#include "mge/util/DrawRectangle.hpp"

DrawRectangle::DrawRectangle()
{
}

DrawRectangle::~DrawRectangle()
{
}

void DrawRectangle::SetXY(int xValue, int yValue)
{
	x = xValue;
	y = yValue;
}

void DrawRectangle::SetSquareSize(int size)
{
	squareSize = size;
}

void DrawRectangle::SetColour(float r, float g, float b, float a)
{
	rectangle.setFillColor(sf::Color(
		std::ceil(r * 255),
		std::ceil(g * 255),
		std::ceil(b * 255),
		std::ceil(a * 255)));
}

int DrawRectangle::luaNewDrawRectangle(lua_State * lua)
{
	DrawRectangle* rectangle;
	int x = LuaWrapper::GetNumber<int>(lua);
	int y = LuaWrapper::GetNumber<int>(lua);
	int squareSize = LuaWrapper::GetNumber<int>(lua);
	//Getting RGBA values from the table.
	float red = LuaWrapper::GetTableValue<float>(lua, "colour", "r");
	float green = LuaWrapper::GetTableValue<float>(lua, "colour", "g");
	float blue = LuaWrapper::GetTableValue<float>(lua, "colour", "b");
	float alpha = LuaWrapper::GetTableValue<float>(lua, "colour", "a");

	size_t nBytes = sizeof(DrawRectangle);
	rectangle = static_cast<DrawRectangle*>(lua_newuserdata(lua, nBytes));
	rectangle->SetXY(x, y);
	rectangle->SetSquareSize(squareSize);
	rectangle->SetColour(red, green, blue, alpha);
	return 1;
}

int DrawRectangle::luaUpdateRectangle(lua_State * lua)
{
	DrawRectangle* rectangle = static_cast<DrawRectangle*>(lua_touserdata(lua, 1));
	float red = LuaWrapper::GetTableValue<float>(lua, "colour", "r");
	float green = LuaWrapper::GetTableValue<float>(lua, "colour", "g");
	float blue = LuaWrapper::GetTableValue<float>(lua, "colour", "b");
	float alpha = LuaWrapper::GetTableValue<float>(lua, "colour", "a");
	rectangle->SetColour(red, green, blue, alpha);
	return 0;
}

static const struct luaL_Reg DrawRectangleMetaLib[] =
{
	{"UpdateRectangle", DrawRectangle::luaUpdateRectangle},
	{NULL, NULL}
};

static const struct luaL_Reg DrawRectangleLib [] =
{
	{"New", DrawRectangle::luaNewDrawRectangle},
	{NULL, NULL}
};

void DrawRectangle::InitializeLua()
{
	lua_State *lua = luaL_newstate();
	luaL_openlibs(lua);

	luaL_newmetatable(lua, "drawRectangle");

	lua_pushstring(lua, "__index");
	lua_pushvalue(lua, -2); //Pushes the metatable
	lua_settable(lua, -3);
	
	luaL_setfuncs(lua, DrawRectangleMetaLib, 0);
	
	luaL_newlib(lua, DrawRectangleLib);
	luaL_getmetatable(lua, "drawRectangle");
	lua_setmetatable(lua, -2);
	lua_setglobal(lua, "DrawRectangle");

	luaL_loadfile(lua, "LuaGameScripts/BaseOrganism.lua");
	lua_call(lua, 0, 0);
}


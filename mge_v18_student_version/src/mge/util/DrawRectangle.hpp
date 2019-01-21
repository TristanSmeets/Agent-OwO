#ifndef DRAWRECTANGLE_HPP
#define DRAWRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include "LuaWrapper.hpp"

///Class that will be used to create rectangles on the screen.
///Will be used in the lua game.
class DrawRectangle
{
public:
	DrawRectangle();
	~DrawRectangle();
	void SetXY(float xValue, float yValue);
	void SetSquareSize(float size);
	void SetColour(float r, float g, float b, float a);
	static int luaNewDrawRectangle(lua_State *lua);
	static int luaUpdateRectangle(lua_State *lua);
	static int luaDraw(lua_State *lua);
	static void InitializeLua();
private:
	sf::RectangleShape* rectangle;
	sf::Color colour;
};

#endif // !DRAWRECTANGLE_HPP


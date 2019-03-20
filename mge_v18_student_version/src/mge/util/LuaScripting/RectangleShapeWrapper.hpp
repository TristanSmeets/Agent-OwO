#ifndef RECTANGLESHAPEWRAPPER_HPP
#define RECTANGLESHAPEWRAPPER_HPP

#include <SFML/Graphics.hpp>
#include <lua.hpp>
#include "LuaWrapper.hpp"

///Class that will be used to create rectangles on the screen.
///Will be used in the lua game.
class RectangleShapeWrapper
{
public:
	RectangleShapeWrapper();
	~RectangleShapeWrapper();
	void SetPosition(float xValue, float yValue);
	void SetSquareSize(float size);
	void SetColour(float r, float g, float b, float a);
	sf::RectangleShape& GetRectangleShape();
	static int luaNewRectangleShapeWrapper(lua_State *lua);
	static int luaSetPosition(lua_State *lua);
	static int luaSetColour(lua_State *lua);
	static int luaSetSquareSize(lua_State *lua);
	static void InitializeLua(lua_State* lua);
private:
	sf::RectangleShape* rectangle;
};

#endif // !RECTANGLESHAPEWRAPPER_HPP


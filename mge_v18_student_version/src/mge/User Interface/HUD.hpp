#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "mge/User Interface/UIStepCounter.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class HUD
{
public:
	HUD(int levelNumber);
	~HUD();
	void Draw(sf::RenderWindow* window);

private:
	UIStepCounter* stepCounter;
	lua_State* luaHUD;
};
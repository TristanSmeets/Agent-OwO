#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "mge/User Interface/UIStepCounter.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/User Interface/Dialogue.hpp"

class HUD : Observer<GeneralEvent>
{
public:
	HUD(int levelNumber);
	~HUD();
	void Draw(sf::RenderWindow* window);
	void OnNotify(const GeneralEvent& info);

private:
	int levelNumber;
	bool showingDialogue = true;
	UIStepCounter* stepCounter = nullptr;
	Dialogue* dialogue = nullptr;
	lua_State* luaHUD;
};
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
	void initialize();

	int levelNumber;
	bool showingDialogue = true;
	UIStepCounter* stepCounter = nullptr;
	Dialogue* dialogue = nullptr;

	sf::Texture* iconTexture;
	sf::Sprite iconSprite;

	lua_State* luaHUD;
};
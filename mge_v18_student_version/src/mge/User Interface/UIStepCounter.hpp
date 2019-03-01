#pragma once
#include "SFML/Graphics.hpp"
#include "mge/core/Observer.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class UIStepCounter : public Observer<GeneralEvent>
{
public:
	UIStepCounter(lua_State* luaHUD, int level);
	~UIStepCounter();
	void OnNotify(const GeneralEvent& info);
	void Draw(sf::RenderWindow* window);

private:
	void resetStepCounter();
	void updateStepCounter(int Number);
	sf::Font font;
	sf::Text stepText;
	sf::Sprite iconImage;
	sf::Texture iconTexture;
	int totalSteps;
	int stepsLeft;
};
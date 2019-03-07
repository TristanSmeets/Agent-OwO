#pragma once
#include "mge/gameplay/Button/Button.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/gameplay/Command/QuitCommand.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class CreditsScreen
{
public:
	CreditsScreen(World* world, sf::RenderWindow* window);
	~CreditsScreen();
	void Draw(sf::RenderWindow* window);

private:
	void initialize();
	World* world;
	Button* backButton;
	GameObject* mouse;
	MouseBehaviour* mouseBehaviour;
	sf::Texture* backgroundTexture;
	sf::Sprite backgroundImage;
};
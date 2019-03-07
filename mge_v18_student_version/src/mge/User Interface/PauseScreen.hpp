#pragma once
#include "SFML/Graphics.hpp"
#include "mge/gameplay/Button/Button.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/gameplay/Command/QuitCommand.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/gameplay/Command/ContinueCommand.hpp"

class PauseScreen
{
public:
	PauseScreen(World* world, sf::RenderWindow* window);
	~PauseScreen();
	void Draw(sf::RenderWindow* window);

private:
	void initialize();
	sf::Texture* backgroundTexture;
	sf::Sprite backgroundImage;
	Button* continueButton;
	Button* quitButton;
	World* world;
	GameObject* mouse;
	MouseBehaviour* mouseBehaviour;
};
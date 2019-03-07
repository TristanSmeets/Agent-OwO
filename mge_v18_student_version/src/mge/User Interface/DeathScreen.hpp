#pragma once
#include "mge/gameplay/Button/Button.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/gameplay/Command/QuitCommand.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/gameplay/Command/RetryCommand.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class DeathScreen
{
public:
	DeathScreen(World* world, sf::Window* window);
	~DeathScreen();
	void Draw(sf::RenderWindow* window);

private:
	void initialize();
	World* world;
	Button* retryButton;
	Button* quitButton;
	GameObject* mouse;
	MouseBehaviour* mouseBehaviour;
	sf::Texture* backgroundTexture;
	sf::Sprite backgroundImage;
};

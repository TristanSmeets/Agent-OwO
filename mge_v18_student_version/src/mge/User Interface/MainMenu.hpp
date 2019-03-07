#pragma once

#include "mge/gameplay/Button/Button.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/gameplay/Command/StartCommand.hpp"
#include "mge/gameplay/Command/ExitCommand.hpp"
#include "mge/gameplay/Command/CreditsCommand.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/core/World.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class MainMenu
{
public:
	MainMenu(World* world, sf::RenderWindow* window);
	~MainMenu();
	void Draw(sf::RenderWindow* window);

private:
	World* world;
	Button* startButton;
	Button* creditsButton;
	Button* exitButton;
	GameObject* mouse;
	MouseBehaviour* mouseBehaviour;
	sf::Texture* backgroundTexture;
	sf::Sprite BackgroundImage;

	void initialize(sf::RenderWindow* window);
};
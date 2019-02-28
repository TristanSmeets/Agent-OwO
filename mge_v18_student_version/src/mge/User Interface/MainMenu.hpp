#pragma once

#include "mge/gameplay/Button/Button.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/gameplay/Command/StartCommand.hpp"
#include "mge/behaviours/MouseBehaviour.hpp"
#include "mge/core/World.hpp"

class MainMenu
{
public:
	MainMenu(World* world, sf::Window* window);
	~MainMenu();

private:
	World* world;
	Button* startButton;
	GameObject* mouse;
	MouseBehaviour* mouseBehaviour;
	Button* exitButton;
};
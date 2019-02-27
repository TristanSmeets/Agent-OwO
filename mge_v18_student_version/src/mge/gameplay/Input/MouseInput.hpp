#pragma once

#include "mge/gameplay/Input/InputHandler.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "SFML/Window/Mouse.hpp"

class MouseInput : public InputHandler
{
	MouseInput(sf::Window* window);
	~MouseInput();
	Command* HandleInput();
	
private:
	bool isColliding(Button* button);
	sf::Window* window;
};
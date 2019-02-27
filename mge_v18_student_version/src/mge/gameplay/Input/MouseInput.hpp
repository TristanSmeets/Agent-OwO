#pragma once

#include "mge/gameplay/Input/InputHandler.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "SFML/Window/Mouse.hpp"

class MouseInput : public InputHandler
{
	MouseInput();
	~MouseInput();
	Command* HandleInput();
	
private:
};
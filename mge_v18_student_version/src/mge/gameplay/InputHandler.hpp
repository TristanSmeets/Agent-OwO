#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/gameplay/Command/Command.hpp"

class InputHandler
{
public:
	InputHandler(MovableBehaviour& movable);
	~InputHandler();
	void HandleInput();

private:
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
};
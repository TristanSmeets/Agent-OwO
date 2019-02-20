#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "mge/gameplay/Input/InputHandler.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

class PlayerInput : public InputHandler
{
public:
	PlayerInput(MovableBehaviour* movable);
	virtual ~PlayerInput();
	Command* HandleInput();
private:
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
};
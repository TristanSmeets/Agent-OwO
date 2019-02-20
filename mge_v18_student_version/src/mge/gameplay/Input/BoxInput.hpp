#pragma once

#include "mge/gameplay/Input/InputHandler.hpp"
#include "mge/gameplay/Command/Command.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

class BoxInput : public InputHandler
{
public:
	BoxInput(MovableBehaviour* movable);
	virtual ~BoxInput();
	Command* HandleInput();
	void PushBox(DIRECTION direction);

private:
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
	Command* directionToMove;
};
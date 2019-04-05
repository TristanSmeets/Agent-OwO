#include "BoxInput.hpp"
#include "mge/gameplay/Command/UpCommand.hpp"
#include "mge/gameplay/Command/DownCommand.hpp"
#include "mge/gameplay/Command/LeftCommand.hpp"
#include "mge/gameplay/Command/RightCommand.hpp"

BoxInput::BoxInput(MovableBehaviour* movable)
{
	moveUp = new UpCommand(*movable);
	moveDown = new DownCommand(*movable);
	moveLeft = new LeftCommand(*movable);
	moveRight = new RightCommand(*movable);
}

BoxInput::~BoxInput()
{
	InputHandler::~InputHandler();
	delete moveUp;
	delete moveDown;
	delete moveLeft;
	delete moveRight;
}

Command * BoxInput::HandleInput()
{
	Command* returnCommand = nullptr;
	if (directionToMove)
	{
		returnCommand = directionToMove;
		directionToMove = nullptr;
	};
	return returnCommand;
}

void BoxInput::PushBox(DIRECTION direction)
{
	switch (direction)
	{
	case DIRECTION::UP:
		directionToMove = moveUp;
		break;
	case DIRECTION::DOWN:
		directionToMove = moveDown;
		break;
	case DIRECTION::LEFT:
		directionToMove = moveLeft;
		break;
	case DIRECTION::RIGHT:
		directionToMove = moveRight;
		break;
	}
}

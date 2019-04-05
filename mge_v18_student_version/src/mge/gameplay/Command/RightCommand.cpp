#include "RightCommand.hpp"


RightCommand::RightCommand(MovableBehaviour & movable) : MoveCommand(movable)
{
}

RightCommand::~RightCommand()
{
	MoveCommand::~MoveCommand();
}

void RightCommand::BoxMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::RIGHT))
	{
		moveObject(current, DIRECTION::RIGHT);
	}
}

void RightCommand::PlayerMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::RIGHT))
	{
		nodeBoxCheck(current, DIRECTION::RIGHT);
		moveObject(current, DIRECTION::RIGHT);
	}
}

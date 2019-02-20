#include "LeftCommand.hpp"

LeftCommand::LeftCommand(MovableBehaviour& movable) : MoveCommand(movable)
{}

LeftCommand::~LeftCommand()
{
	std::cout << "GC running on:LeftCommand\n";
	MoveCommand::~MoveCommand();
}

void LeftCommand::BoxMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::LEFT))
	{
		Node* destination = current->GetConnectionAt(DIRECTION::LEFT);
		moveObject(current, DIRECTION::LEFT);
	}
}

void LeftCommand::PlayerMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::LEFT))
	{
		nodeBoxCheck(current, DIRECTION::LEFT);
		moveObject(current, DIRECTION::LEFT);
	}
}

#include "UpCommand.hpp"

UpCommand::UpCommand(MovableBehaviour& movable) : MoveCommand(movable)
{}

UpCommand::~UpCommand()
{
	std::cout << "GC running on:UpCommand\n";
	MoveCommand::~MoveCommand();
}

void UpCommand::BoxMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::UP))
	{
		Node* destination = current->GetConnectionAt(DIRECTION::UP);
		moveObject(current, DIRECTION::UP);
	}
}

void UpCommand::PlayerMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::UP))
	{
		nodeBoxCheck(current, DIRECTION::UP);
		moveObject(current, DIRECTION::UP);
	}
}


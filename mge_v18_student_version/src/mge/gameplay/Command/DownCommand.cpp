#include "DownCommand.hpp"

DownCommand::DownCommand(MovableBehaviour& movable) : MoveCommand(movable)
{}

DownCommand::~DownCommand()
{
	std::cout << "GC running on:DownCommand\n";
	MoveCommand::~MoveCommand();
}

void DownCommand::BoxMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::DOWN))
	{
		Node* destination = current->GetConnectionAt(DIRECTION::DOWN);
		moveObject(current, DIRECTION::DOWN);
	}
}

void DownCommand::PlayerMovement()
{
	Node* current = movableObject.GetCurrentNode();
	if (checkHasNeighbour(current, DIRECTION::DOWN))
	{
		nodeBoxCheck(current, DIRECTION::DOWN);
		moveObject(current, DIRECTION::DOWN);
	}
}

#include "UpCommand.hpp"

UpCommand::UpCommand(MovableBehaviour& movable) : Command(), movableObject(movable)
{}

UpCommand::~UpCommand()
{
	std::cout << "GC running on:UpCommand\n";
}

void UpCommand::Execute()
{
	std::cout << "Executing UpCommand\n";
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::UP))
	{
		std::cout << "Current Node has UP connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::UP);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "Destination Node is walkable\n";
			movableObject.SetDestination(destinationNode);
			movableObject.Move();
		}
		else
			std::cout << "NODE isn't walkable\n";
	}
	else
		std::cout << "No UP connection\n";
}


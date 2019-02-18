#include "DownCommand.hpp"

DownCommand::DownCommand(MovableBehaviour& movable) : Command(), movableObject(movable)
{}

DownCommand::~DownCommand()
{
	std::cout << "GC running on:DownCommand\n";
}

void DownCommand::Execute()
{
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::DOWN))
	{
		std::cout << "Current Node has DOWN connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::DOWN);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "Destination Node is walkable\n";
			movableObject.SetDestination(destinationNode);
		}
	}
}

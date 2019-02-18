#include "UpCommand.hpp"

UpCommand::UpCommand() : Command()
{}

UpCommand::~UpCommand()
{
	std::cout << "GC running on:UpCommand\n";
}

void UpCommand::Execute(MovableBehaviour& movableObject)
{
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::UP))
	{
		std::cout << "Current Node has UP connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::UP);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "Destination Node is walkable\n";
			movableObject.SetDestination(destinationNode);
		}
	}
}


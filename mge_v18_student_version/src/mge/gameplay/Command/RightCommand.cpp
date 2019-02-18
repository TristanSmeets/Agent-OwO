#include "RightCommand.hpp"

RightCommand::RightCommand(MovableBehaviour & movable) : Command(), movableObject(movable)
{
}

RightCommand::~RightCommand()
{
	std::cout << "GC running on:RightCommand\n";
}

void RightCommand::Execute()
{
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::RIGHT))
	{
		std::cout << "Current Node has RIGHT connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::RIGHT);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "Destination Node is walkable\n";
			movableObject.SetDestination(destinationNode);
		}
	}
}

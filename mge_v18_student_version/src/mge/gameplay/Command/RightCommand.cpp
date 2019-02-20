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
	std::cout << "Executing RightCommand\n";

	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::RIGHT))
	{
		std::cout << "Current Node has RIGHT connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::RIGHT);
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
		std::cout << "No RIGHT connection\n";
}

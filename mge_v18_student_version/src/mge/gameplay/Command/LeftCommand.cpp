#include "LeftCommand.hpp"

LeftCommand::LeftCommand(MovableBehaviour& movable) : Command(), movableObject(movable)
{}

LeftCommand::~LeftCommand()
{
	std::cout << "GC running on:LeftCommand\n";
}

void LeftCommand::Execute()
{
	std::cout << "Executing LeftCommand\n";
	Node* currentNode = movableObject.GetCurrentNode();
	
	if (checkHasNeighbour(currentNode, DIRECTION::LEFT))
	{
		std::cout << "Current Node has LEFT connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::LEFT);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "Destination Node is walkable\n";
			movableObject.SetDestination(destinationNode);
			//movableObject.move();
		}
	}
	else
		std::cout << "No LEFT connection\n";
}

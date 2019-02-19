#include "DownCommand.hpp"

DownCommand::DownCommand(MovableBehaviour& movable) : Command(), movableObject(movable)
{}

DownCommand::~DownCommand()
{
	std::cout << "GC running on:DownCommand\n";
}

void DownCommand::Execute()
{
	std::cout << "Executing DownCommand\n";
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::DOWN))
	{
		std::cout << "Current Node has DOWN connection\n";
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::DOWN);
		if (destinationNode->GetIsWalkable())
		{
			std::cout << "NODE is walkable\n";
			movableObject.SetDestination(destinationNode);
			movableObject.move();
		}
		else
			std::cout << "NODE isn't walkable\n";
	}
	else
		std::cout << "No DOWN connection\n";
}

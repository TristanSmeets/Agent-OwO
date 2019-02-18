#include "Command.hpp"
#include <iostream>

Command::Command()
{
}

Command::~Command()
{
	std::cout << "GC running on:Command\n";
}

bool Command::checkHasNeighbour(Node * node, DIRECTION direction)
{

	if (nullptr != node->GetConnectionAt(direction))
		return true;
	else
		return false;
}

bool Command::checkIsWalkable(Node * node)
{
	return node->GetIsWalkable();
}

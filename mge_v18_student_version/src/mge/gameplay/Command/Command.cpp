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
	return node->HasConnection(direction);
}

bool Command::checkIsWalkable(Node * node)
{
	return node->GetIsWalkable();
}

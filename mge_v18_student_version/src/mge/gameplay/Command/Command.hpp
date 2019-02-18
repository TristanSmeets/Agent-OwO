#pragma once

#include "mge/gameplay/Node.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute(MovableBehaviour& movableObject) = 0;
protected:
	bool checkHasNeighbour(Node* node, DIRECTION direction);
	bool checkIsWalkable(Node* node);
};

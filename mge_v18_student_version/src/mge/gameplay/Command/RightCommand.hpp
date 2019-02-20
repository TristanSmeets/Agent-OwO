#pragma once

#include "mge/gameplay/Command/Command.hpp"

class RightCommand : public Command
{
public:
	RightCommand(MovableBehaviour& movable);
	virtual ~RightCommand();
	void Execute();
	void BoxMovement();
	void MoveObject(Node * destination, Node * currentNode);
	void PlayerMovement();
	void Walkable(Node * destinationNode);
private:
	MovableBehaviour& movableObject;
};
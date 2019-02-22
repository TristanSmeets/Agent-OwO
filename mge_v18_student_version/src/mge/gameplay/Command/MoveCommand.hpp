#pragma once

#include "mge/gameplay/Command\Command.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/BoxInput.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class MoveCommand : public Command
{
public:
	MoveCommand(MovableBehaviour& movable);
	virtual ~MoveCommand();
	void Execute();
	virtual void BoxMovement() = 0;
	virtual void PlayerMovement() = 0;
protected:
	void moveObject(Node* current, DIRECTION direction);
	void nodeBoxCheck(Node* current, DIRECTION direction);
	const EventInfo& createMovedEvent();
	MovableBehaviour& movableObject;
};

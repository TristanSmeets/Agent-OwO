#pragma once

#include "mge/gameplay/Command/MoveCommand.hpp"

class UpCommand : public MoveCommand
{
public:
	UpCommand(MovableBehaviour& movable);
	virtual ~UpCommand();
	void BoxMovement();
	void PlayerMovement();
};
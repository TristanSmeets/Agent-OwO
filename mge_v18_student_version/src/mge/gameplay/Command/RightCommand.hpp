#pragma once

#include "mge/gameplay/Command/MoveCommand.hpp"

class RightCommand : public MoveCommand
{
public:
	RightCommand(MovableBehaviour& movable);
	virtual ~RightCommand();
	void BoxMovement();
	void PlayerMovement();
};
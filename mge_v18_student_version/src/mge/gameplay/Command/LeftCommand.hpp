#pragma once
#include "mge/gameplay/Command/MoveCommand.hpp"

class LeftCommand : public MoveCommand
{
public:
	LeftCommand(MovableBehaviour& movable);
	virtual ~LeftCommand();
	void BoxMovement();
	void PlayerMovement();
};
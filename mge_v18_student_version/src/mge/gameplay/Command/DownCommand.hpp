#pragma once
#include "mge/gameplay/Command/MoveCommand.hpp"

class DownCommand : public MoveCommand
{
public:
	DownCommand(MovableBehaviour& movable);
	virtual ~DownCommand();
	void BoxMovement();
	void PlayerMovement();
};
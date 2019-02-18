#pragma once

#include "mge/gameplay/Command/Command.hpp"

class RightCommand : public Command
{
public:
	RightCommand(MovableBehaviour& movable);
	virtual ~RightCommand();
	void Execute();
private:
	MovableBehaviour& movableObject;
};
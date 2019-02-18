#pragma once

#include "mge/gameplay/Command/Command.hpp"

class UpCommand : public Command
{
public:
	UpCommand(MovableBehaviour& movable);
	virtual ~UpCommand();
	void Execute();
private:
	MovableBehaviour& movableObject;
};
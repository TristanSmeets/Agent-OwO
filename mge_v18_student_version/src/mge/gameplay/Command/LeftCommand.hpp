#pragma once
#include "mge/gameplay/Command/Command.hpp"

class LeftCommand : public Command
{
public:
	LeftCommand(MovableBehaviour& movable);
	virtual ~LeftCommand();
	void Execute();
private:
	MovableBehaviour& movableObject;
};
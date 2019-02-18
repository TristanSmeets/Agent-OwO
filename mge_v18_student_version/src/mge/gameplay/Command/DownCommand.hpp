#pragma once
#include "mge/gameplay/Command/Command.hpp"

class DownCommand : public Command
{
public:
	DownCommand(MovableBehaviour& movable);
	virtual ~DownCommand();
	void Execute();
private:
	MovableBehaviour& movableObject;
};
#pragma once

#include "mge/gameplay/Command/Command.hpp"

class UpCommand : public Command
{
public:
	UpCommand();
	virtual ~UpCommand();
	void Execute(MovableBehaviour& movableObject);
};
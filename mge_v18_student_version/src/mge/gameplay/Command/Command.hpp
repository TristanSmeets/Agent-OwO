#pragma once

#include "mge/gameplay/Node.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

class Command
{
public:
	Command();
	virtual ~Command();
	virtual void Execute() = 0;
};

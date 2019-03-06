#pragma once

#include "mge/gameplay/Command/Command.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class RetryCommand : public Command
{
public:
	RetryCommand();
	~RetryCommand();
	void Execute();
};
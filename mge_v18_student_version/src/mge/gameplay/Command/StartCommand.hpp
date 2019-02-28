#pragma once

#include "mge/gameplay/Command/Command.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class StartCommand : public Command
{
public:
	StartCommand();
	~StartCommand();
	void Execute();
};
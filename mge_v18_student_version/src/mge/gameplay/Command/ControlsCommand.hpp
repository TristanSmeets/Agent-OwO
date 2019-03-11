#pragma once
#include "mge/gameplay/Command/Command.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class ControlsCommand : public Command
{
public:
	ControlsCommand();
	~ControlsCommand();
	void Execute();
};
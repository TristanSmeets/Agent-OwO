#pragma once
#include "mge/util/EventQueue/EventQueue.hpp"
#include "Command.hpp"

class QuitCommand : public Command
{
public:
	QuitCommand();
	~QuitCommand();
	void Execute();
};
#pragma once
#include "mge/gameplay/Command/Command.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class ContinueCommand : public Command
{
public:
	ContinueCommand();
	~ContinueCommand();
	void Execute();
};
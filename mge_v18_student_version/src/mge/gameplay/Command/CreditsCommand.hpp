#pragma once
#include "mge/gameplay/Command/Command.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class CreditsCommand : public Command
{
public:
	CreditsCommand();
	~CreditsCommand();
	void Execute();
};
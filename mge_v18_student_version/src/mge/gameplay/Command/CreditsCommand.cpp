#include "CreditsCommand.hpp"

CreditsCommand::CreditsCommand()
{
}

CreditsCommand::~CreditsCommand()
{
}

void CreditsCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.showCreditsScreen = true;
	EventQueue::QueueEvent(info);
	std::cout << "Queueing event.\n";
}
#include "RetryCommand.hpp"

RetryCommand::RetryCommand() : Command()
{
}

RetryCommand::~RetryCommand()
{
	std::cout << "GC running on:RetryCommand.\n";
}

void RetryCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.resetLevel = true;
	EventQueue::QueueEvent(info);
}
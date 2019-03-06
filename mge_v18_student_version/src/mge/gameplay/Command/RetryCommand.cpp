#include "RetryCommand.hpp"

RetryCommand::RetryCommand() : Command()
{
	std::cout << "Creating RetryCommand.\n";
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
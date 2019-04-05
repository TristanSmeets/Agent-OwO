#include "RetryCommand.hpp"

RetryCommand::RetryCommand() : Command()
{
}

RetryCommand::~RetryCommand()
{
}

void RetryCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.resetLevel = true;
	EventQueue::QueueEvent(info);
}
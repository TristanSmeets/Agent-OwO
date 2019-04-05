#include "StartCommand.hpp"

StartCommand::StartCommand() : Command()
{
}

StartCommand::~StartCommand()
{
}

void StartCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.startGame = true;
	EventQueue::QueueEvent(info);
}

#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command()
{
}

QuitCommand::~QuitCommand()
{
}

void QuitCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.showMainMenu = true;
	EventQueue::QueueEvent(info);
}
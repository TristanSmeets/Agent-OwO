#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command()
{
}

QuitCommand::~QuitCommand()
{
	std::cout << "GC running on:QuitCommand.\n";
}

void QuitCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.showMainMenu = true;
	EventQueue::QueueEvent(info);
}
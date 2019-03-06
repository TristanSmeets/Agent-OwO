#include "QuitCommand.hpp"

QuitCommand::QuitCommand() : Command()
{
	std::cout << "Creating QuitCommand.\n";
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
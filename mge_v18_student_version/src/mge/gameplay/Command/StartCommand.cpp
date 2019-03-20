#include "StartCommand.hpp"

StartCommand::StartCommand() : Command()
{
}

StartCommand::~StartCommand()
{
	std::cout << "GC running on:StartCommand.\n";
}

void StartCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.startGame = true;
	EventQueue::QueueEvent(info);
}

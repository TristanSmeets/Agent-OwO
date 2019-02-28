#include "StartCommand.hpp"

StartCommand::StartCommand() : Command()
{
	std::cout << "Creating StartCommand.\n";
}

StartCommand::~StartCommand()
{
	std::cout << "GC running on:StartCommand.\n";
}

void StartCommand::Execute()
{
	std::cout << "Queueing startevent.\n";
	GeneralEvent info = GeneralEvent();
	info.startGame = true;
	EventQueue::QueueEvent(info);
}

#include "ContinueCommand.hpp"

ContinueCommand::ContinueCommand() : Command()
{
}

ContinueCommand::~ContinueCommand()
{
	std::cout << "GC running on:ContinueCommand.\n";
}

void ContinueCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.closePauseScreen = true;
	EventQueue::QueueEvent(info);

}

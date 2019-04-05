#include "ContinueCommand.hpp"

ContinueCommand::ContinueCommand() : Command()
{
}

ContinueCommand::~ContinueCommand()
{
}

void ContinueCommand::Execute()
{
	GeneralEvent info = GeneralEvent();
	info.closePauseScreen = true;
	EventQueue::QueueEvent(info);

}

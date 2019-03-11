#include "ControlsCommand.hpp"

ControlsCommand::ControlsCommand()
{
}

ControlsCommand::~ControlsCommand()
{
}

void ControlsCommand::Execute()
{
	GeneralEvent info;
	info.showControlScreen = true;
	EventQueue::QueueEvent(info);
}


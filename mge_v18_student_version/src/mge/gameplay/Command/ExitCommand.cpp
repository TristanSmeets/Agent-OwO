#include "ExitCommand.hpp"

ExitCommand::ExitCommand(sf::Window* window) : Command(), window(window)
{
}

ExitCommand::~ExitCommand()
{
}

void ExitCommand::Execute()
{
	window->close();
}
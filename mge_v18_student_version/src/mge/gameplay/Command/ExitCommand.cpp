#include "ExitCommand.hpp"

ExitCommand::ExitCommand(sf::Window* window) : Command(), window(window)
{
}

ExitCommand::~ExitCommand()
{
	std::cout << "GC running on:ExitCommand.\n";
}

void ExitCommand::Execute()
{
	window->close();
}
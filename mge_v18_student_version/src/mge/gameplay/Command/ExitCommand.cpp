#include "ExitCommand.hpp"

ExitCommand::ExitCommand(sf::Window* window) : Command(), window(window)
{
	std::cout << "Creating ExitCommand.\n";
}

ExitCommand::~ExitCommand()
{
	std::cout << "GC running on:ExitCommand.\n";
}

void ExitCommand::Execute()
{
	std::cout << "Closing Game.\n";
	window->close();
}
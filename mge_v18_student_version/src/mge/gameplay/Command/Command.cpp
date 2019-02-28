#include "Command.hpp"
#include <iostream>

Command::Command()
{
}

Command::~Command()
{
	std::cout << "GC running on:Command\n";
}

#pragma once

#include "mge/gameplay/Command/Command.hpp"
#include "SFML/Window.hpp"

class ExitCommand : public Command
{
public:
	ExitCommand(sf::Window* window);
	~ExitCommand();
	void Execute();

private:
	sf::Window* window;
};
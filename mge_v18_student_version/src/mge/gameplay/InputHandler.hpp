#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "mge/gameplay/Command/Command.hpp"

class Command;

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();
	virtual Command* HandleInput() = 0;
private:
};
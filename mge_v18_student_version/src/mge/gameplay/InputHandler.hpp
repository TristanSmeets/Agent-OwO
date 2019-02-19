#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/gameplay/Command/Command.hpp"

class Command;

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void HandleInput();
	void SetMoveUp(Command* upCommand);
	void SetMoveDown(Command* downCommand);
	void SetMoveLeft(Command* leftCommand);
	void SetMoveRight(Command* rightCommand);

private:
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
	bool up;
	bool down;
	bool left;
	bool right;
};
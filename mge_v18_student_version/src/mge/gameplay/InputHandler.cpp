#include "InputHandler.hpp"
#include <iostream>


InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
	std::cout << "GC running on:InputHandler\n";
	delete moveUp;
	delete moveDown;
	delete moveLeft;
	delete moveRight;
}

Command* InputHandler::HandleInput()
{
	//UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		return moveUp;
	//DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		return moveDown;
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		return moveLeft;
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		return moveRight;
	return nullptr;
}

void InputHandler::SetMoveUp(Command * upCommand)
{
	moveUp = upCommand;
}

void InputHandler::SetMoveDown(Command * downCommand)
{
	moveDown = downCommand;
}

void InputHandler::SetMoveLeft(Command * leftCommand)
{
	moveLeft = leftCommand;
}

void InputHandler::SetMoveRight(Command * rightCommand)
{
	moveRight = rightCommand;
}

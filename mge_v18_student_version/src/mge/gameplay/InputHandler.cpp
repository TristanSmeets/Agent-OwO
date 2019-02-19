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

void InputHandler::HandleInput()
{
	//UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true && 
		up == false)
	{
		std::cout << "Pressing UP\n";
		moveUp->Execute();
	}
	//DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true &&
		down == false)
	{
		std::cout << "Pressing DOWN\n";
		moveDown->Execute();
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true &&
		left == false)
	{
		std::cout << "Pressing LEFT\n";
		moveLeft->Execute();
	}
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true &&
		right == false)
	{
		std::cout << "Pressing RIGHT\n";
		moveRight->Execute();
	}
	up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	right= sf::Keyboard::isKeyPressed(sf::Keyboard::D);
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

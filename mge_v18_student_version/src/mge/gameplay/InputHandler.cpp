#include "InputHandler.hpp"
#include "mge/gameplay/Command/UpCommand.hpp"
#include "mge/gameplay/Command/DownCommand.hpp"
#include "mge/gameplay/Command/LeftCommand.hpp"
#include "mge/gameplay/Command/RightCommand.hpp"
#include <iostream>


InputHandler::InputHandler(MovableBehaviour & movable) :
	moveUp(new UpCommand(movable)), moveDown(new DownCommand(movable)), 
	moveLeft(new LeftCommand(movable)), moveRight(new RightCommand(movable))
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		std::cout << "Pressing UP\n";
		//moveUp->Execute();
	}
	//DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		std::cout << "Pressing DOWN\n";
		//moveDown->Execute();
	}
	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Pressing LEFT\n";
		//moveLeft->Execute();
	}
	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "Pressing RIGHT\n";
		//moveRight->Execute();
	}
}

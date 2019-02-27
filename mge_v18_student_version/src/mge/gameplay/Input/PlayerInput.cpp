#include "PlayerInput.hpp"
#include "mge/gameplay/Command/UpCommand.hpp"
#include "mge/gameplay/Command/DownCommand.hpp"
#include "mge/gameplay/Command/LeftCommand.hpp"
#include "mge/gameplay/Command/RightCommand.hpp"

PlayerInput::PlayerInput(MovableBehaviour* movable)
{
	moveUp = new UpCommand(*movable);
	moveDown = new DownCommand(*movable);
	moveLeft = new LeftCommand(*movable);
	moveRight = new RightCommand(*movable);
}

PlayerInput::~PlayerInput()
{
	InputHandler::~InputHandler();
	std::cout << "GC running on:PlayerInput\n";
	delete moveUp;
	delete moveDown;
	delete moveLeft;
	delete moveRight;
}

Command * PlayerInput::HandleInput()
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) &&
		buttonPressed == false)
	{
		GeneralEvent info;
		info.resetLevel = true;
		EventQueue::QueueEvent(info);
		buttonPressed = true;
	}
	buttonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
	return nullptr;
}

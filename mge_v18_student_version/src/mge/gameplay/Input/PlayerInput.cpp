#include "PlayerInput.hpp"
#include "mge/gameplay/Command/UpCommand.hpp"
#include "mge/gameplay/Command/DownCommand.hpp"
#include "mge/gameplay/Command/LeftCommand.hpp"
#include "mge/gameplay/Command/RightCommand.hpp"

PlayerInput::PlayerInput(MovableBehaviour* movable) : InputHandler(), Observer<GeneralEvent>()
{
	moveUp = new UpCommand(*movable);
	moveDown = new DownCommand(*movable);
	moveLeft = new LeftCommand(*movable);
	moveRight = new RightCommand(*movable);
	EventQueue::AddObserver(this);
}

PlayerInput::~PlayerInput()
{
	InputHandler::~InputHandler();
	std::cout << "GC running on:PlayerInput\n";
	delete moveUp;
	delete moveDown;
	delete moveLeft;
	delete moveRight;
	EventQueue::RemoveObserver(this);
}

Command * PlayerInput::HandleInput()
{
	if (canMove)
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
	}
	buttonPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spacePressed == false)
	{
		GeneralEvent info;
		info.nextDialogue = true;
		EventQueue::QueueEvent(info);
		buttonPressed = true;
	}
	spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && escPressed == false)
	{
		GeneralEvent info;
		info.showPauseScreen = true;
		EventQueue::QueueEvent(info);
		escPressed = true;
	}
	escPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	return nullptr;
}

void PlayerInput::OnNotify(const GeneralEvent & info)
{
	if (info.isDialogueCompleted || info.resetLevel|| info.closePauseScreen)
		canMove = true;
	if (info.showEndDialogue || info.showGameOver || info.showPauseScreen)
		canMove = false;
}

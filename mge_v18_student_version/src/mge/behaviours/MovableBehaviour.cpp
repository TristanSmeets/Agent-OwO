#include "MovableBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/PlayerInput.hpp"
#include "mge/gameplay/Input/BoxInput.hpp"
#include <iostream>


MovableBehaviour::MovableBehaviour() : AbstractBehaviour()
{
	std::cout << "Creating MovableBehavior\n";
	inputHandler = new PlayerInput(this);
}

MovableBehaviour::MovableBehaviour(MOVABLE_TYPE movable) : AbstractBehaviour(), movableType(movable)
{
	std::cout << "Creating MovableBehaviour\n";
	switch (movable)
	{
	case MOVABLE_TYPE::BOX_OBJECT:
		inputHandler = new BoxInput(this);
		break;
	case MOVABLE_TYPE::PLAYER_OBJECT:
		inputHandler = new PlayerInput(this);
		break;
	}
}

MovableBehaviour::~MovableBehaviour()
{
	std::cout << "GC running on:MovableBehaviour\n";
	AbstractBehaviour::~AbstractBehaviour();
	currentNode = nullptr;
	delete inputHandler;
}

Node * MovableBehaviour::GetCurrentNode()
{
	return currentNode;
}

void MovableBehaviour::SetDestination(Node * node)
{
	destinationNode = node;
}

void MovableBehaviour::SetCurrentNode(Node * node)
{
	currentNode = node;
}

void MovableBehaviour::update(float pStep)
{
	Command* command = inputHandler->HandleInput();
	if (command && buttonPushed == false)
	{
		command->Execute();
		buttonPushed = true;
	}
	buttonPushed = command != nullptr;
}

void MovableBehaviour::Move()
{
	_owner->setLocalPosition(destinationNode->GetPosition());
	currentNode = destinationNode;
}

MOVABLE_TYPE MovableBehaviour::GetMovableType()
{
	return movableType;
}

InputHandler * MovableBehaviour::GetInputHandler()
{
	return inputHandler;
}

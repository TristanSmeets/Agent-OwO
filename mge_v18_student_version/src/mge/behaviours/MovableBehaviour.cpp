#include "MovableBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/PlayerInput.hpp"
#include "mge/gameplay/Input/BoxInput.hpp"
#include <iostream>


MovableBehaviour::MovableBehaviour() : AbstractBehaviour()
{
	inputHandler = new PlayerInput(this);
}

MovableBehaviour::MovableBehaviour(MOVABLE_TYPE movable) : AbstractBehaviour(), movableType(movable)
{
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
	std::cout << "\nGC running on:MovableBehaviour\n";
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
	currentNode = destinationNode;
	_owner->setLocalPosition(currentNode->GetPosition());
}

MOVABLE_TYPE MovableBehaviour::GetMovableType()
{
	return movableType;
}

InputHandler * MovableBehaviour::GetInputHandler()
{
	return inputHandler;
}

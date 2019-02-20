#include "MovableBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/PlayerInput.hpp"
#include <iostream>


MovableBehaviour::MovableBehaviour() : AbstractBehaviour()
{
	std::cout << "Creating MovableBehavior\n";
	inputHandler = new PlayerInput(this);
}

MovableBehaviour::MovableBehaviour(Node * startingNode) : AbstractBehaviour(), currentNode(startingNode)
{
	std::cout << "Creating MovableBehaviour at:" << startingNode->GetPosition() << std::endl;
	inputHandler = new PlayerInput(this);
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

void MovableBehaviour::move()
{
	_owner->setLocalPosition(destinationNode->GetPosition());
	currentNode = destinationNode;
}

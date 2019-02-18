#include "MovableBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>

MovableBehaviour::MovableBehaviour(Node * startingNode) : currentNode(startingNode), inputHandler(InputHandler(*this))
{
	std::cout << "Creating MovableBehaviour at:" << startingNode->GetPosition() << std::endl;
}

MovableBehaviour::~MovableBehaviour()
{
	std::cout << "GC running on:MovableBehaviour\n";
	AbstractBehaviour::~AbstractBehaviour();
	currentNode = nullptr;
}

Node * MovableBehaviour::GetCurrentNode()
{
	return currentNode;
}

void MovableBehaviour::SetDestination(Node * node)
{
	currentNode = node;
}

InputHandler & MovableBehaviour::GetInputHandler()
{
	return inputHandler;
}

void MovableBehaviour::update(float pStep)
{
	inputHandler.HandleInput();
	move();
}

void MovableBehaviour::move()
{
	//Do some stuff
	if (currentNode->GetPosition() != _owner->getLocalPosition())
	{
		glm::vec3 translation = currentNode->GetPosition() - _owner->getLocalPosition();
		_owner->translate(translation);
	}
}

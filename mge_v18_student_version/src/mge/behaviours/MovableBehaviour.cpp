#include "MovableBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Command/UpCommand.hpp"
#include "mge/gameplay/Command/DownCommand.hpp"
#include "mge/gameplay/Command/LeftCommand.hpp"
#include "mge/gameplay/Command/RightCommand.hpp"
#include <iostream>

MovableBehaviour::MovableBehaviour(Node * startingNode) : currentNode(startingNode)
{
	std::cout << "Creating MovableBehaviour at:" << startingNode->GetPosition() << std::endl;
	inputHandler = new InputHandler();
	inputHandler->SetMoveUp(new UpCommand(*this));
	inputHandler->SetMoveDown(new DownCommand(*this));
	inputHandler->SetMoveLeft(new LeftCommand(*this));
	inputHandler->SetMoveRight(new LeftCommand(*this));
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
	currentNode = node;
}

void MovableBehaviour::update(float pStep)
{
	inputHandler->HandleInput();
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

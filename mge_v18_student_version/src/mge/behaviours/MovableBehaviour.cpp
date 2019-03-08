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

void MovableBehaviour::RotateOwner(DIRECTION direction)
{
	glm::mat4 rotationMatrix;

	switch (direction)
	{
	case DIRECTION::UP:
		rotationMatrix = glm::toMat4(glm::quat(.70711f, 0, -.70711f, 0));
		break;
	case DIRECTION::LEFT:
		rotationMatrix = glm::toMat4(glm::quat(1, 0, 0, 0));
		break;
	case DIRECTION::RIGHT:
		rotationMatrix = glm::toMat4(glm::quat(0, 0, 1, 0));
		break;
	case DIRECTION::DOWN:
		rotationMatrix = glm::toMat4(glm::quat(.70711f, 0, .70711f, 0));
		break;
	}
	glm::mat4 newTransform = glm::translate(currentNode->GetPosition()) * rotationMatrix;
	_owner->setTransform(newTransform);
}

MOVABLE_TYPE MovableBehaviour::GetMovableType()
{
	return movableType;
}

InputHandler * MovableBehaviour::GetInputHandler()
{
	return inputHandler;
}

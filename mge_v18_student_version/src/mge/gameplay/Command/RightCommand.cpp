#include "RightCommand.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/BoxInput.hpp"

RightCommand::RightCommand(MovableBehaviour & movable) : Command(), movableObject(movable)
{
}

RightCommand::~RightCommand()
{
	std::cout << "GC running on:RightCommand\n";
}

void RightCommand::Execute()
{
	if (movableObject.GetMovableType() == MOVABLE_TYPE::PLAYER_OBJECT)
		PlayerMovement();
	if (movableObject.GetMovableType() == MOVABLE_TYPE::BOX_OBJECT)
		BoxMovement();
}

void RightCommand::BoxMovement()
{
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::RIGHT))
	{
		Node* destination = currentNode->GetConnectionAt(DIRECTION::RIGHT);
		MoveObject(destination, currentNode);
	}
}

void RightCommand::MoveObject(Node * destination, Node * currentNode)
{
	if (destination->GetIsWalkable())
	{
		movableObject.SetDestination(destination);
		movableObject.Move();
		destination->SetNodeType(currentNode->GetNodeType());
		destination->SetCurrentGameObject(currentNode->GetCurrentGameObject());
		currentNode->ResetNodeType();
		currentNode->ClearCurrentGameObject();
	}
}

void RightCommand::PlayerMovement()
{
	Node* currentNode = movableObject.GetCurrentNode();
	if (checkHasNeighbour(currentNode, DIRECTION::RIGHT))
	{
		Node* destinationNode = currentNode->GetConnectionAt(DIRECTION::RIGHT);

		//Check if the node is of the boxType.
		if (destinationNode->GetNodeType() == NODETYPE::BOX)
		{
			GameObject* box = destinationNode->GetCurrentGameObject();
			MovableBehaviour* movable = dynamic_cast<MovableBehaviour*>(box->getBehaviour());
			BoxInput* boxInput = dynamic_cast<BoxInput*>(movable->GetInputHandler());
			boxInput->PushBox(DIRECTION::RIGHT);
		}
		MoveObject(destinationNode, currentNode);
	}
	else
		std::cout << "No RIGHT connection\n";
}

void RightCommand::Walkable(Node * destinationNode)
{
	if (destinationNode->GetIsWalkable())
	{
		std::cout << "Destination Node is walkable\n";
		movableObject.SetDestination(destinationNode);
		movableObject.Move();
	}
	else
		std::cout << "NODE isn't walkable\n";
}

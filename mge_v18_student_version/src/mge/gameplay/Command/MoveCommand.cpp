#include "MoveCommand.hpp"

MoveCommand::MoveCommand(MovableBehaviour & movable) : Command(), movableObject(movable)
{
}

MoveCommand::~MoveCommand()
{
	std::cout << "GC running on:MoveCommand\n";
	Command::~Command();
}

void MoveCommand::Execute()
{
	if (movableObject.GetMovableType() == MOVABLE_TYPE::PLAYER_OBJECT)
		PlayerMovement();
	if (movableObject.GetMovableType() == MOVABLE_TYPE::BOX_OBJECT)
		BoxMovement();
}

void MoveCommand::moveObject(Node * current, DIRECTION direction)
{
	Node* destination = current->GetConnectionAt(direction);
	if (destination->GetIsWalkable())
	{
		switch (movableObject.GetMovableType())
		{
		case MOVABLE_TYPE::PLAYER_OBJECT:
			destination->SetNodeType(NODETYPE::GENERIC);
			break;
		case MOVABLE_TYPE::BOX_OBJECT:
			destination->SetNodeType(NODETYPE::BOX);
			break;
		}

		destination->SetCurrentGameObject(current->GetCurrentGameObject());
		current->ResetNodeType();
		current->ClearCurrentGameObject();
		movableObject.SetDestination(destination);
		movableObject.Move();
	}
}

void MoveCommand::nodeBoxCheck(Node * current, DIRECTION direction)
{
	Node* destination = current->GetConnectionAt(direction);
	if (destination->GetNodeType() == NODETYPE::BOX)
	{
		GameObject* box = destination->GetCurrentGameObject();
		MovableBehaviour* movable = dynamic_cast<MovableBehaviour*>(box->getBehaviour());
		BoxInput* boxInput = dynamic_cast<BoxInput*>(movable->GetInputHandler());
		boxInput->PushBox(direction);
		movableObject.SetDestination(destination);
		movableObject.Move();
	}
}
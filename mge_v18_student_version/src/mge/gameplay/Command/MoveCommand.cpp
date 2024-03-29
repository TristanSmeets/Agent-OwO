#include "MoveCommand.hpp"

MoveCommand::MoveCommand(MovableBehaviour & movable) : Command(), movableObject(movable)
{
}

MoveCommand::~MoveCommand()
{
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
			EventQueue::QueueEvent((*createMovedEvent()));
			break;
		case MOVABLE_TYPE::BOX_OBJECT:
			destination->SetNodeType(NODETYPE::BOX);
			lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
			float pitch = LuaWrapper::GetNumber<float>(luaAudio, "PushPitch");
			AudioLocator::GetAudio()->GetSoundEffect(SFX_PUSHBOX).SetPitch(pitch);
			AudioLocator::GetAudio()->PlaySoundEffect(SFX_PUSHBOX);
			LuaWrapper::CloseLuaState(luaAudio);
			break;
		}

		destination->SetCurrentGameObject(current->GetCurrentGameObject());
		current->ResetNodeType();
		current->ClearCurrentGameObject();
		movableObject.SetDestination(destination);
		movableObject.Move();
		movableObject.RotateOwner(direction);
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

		if (destination->HasConnection(direction))
		{
			Node * directionNode = destination->GetConnectionAt(direction);
			if (directionNode->GetIsWalkable())
			{
				movableObject.SetDestination(destination);
				movableObject.Move();
				movableObject.RotateOwner(direction);
				EventQueue::QueueEvent((*createMovedEvent()));
			}
		}
	}
}

GeneralEvent* MoveCommand::createMovedEvent()
{
	GeneralEvent* info = new GeneralEvent();
	info->stepsTaken = 1;
	return info;
}

bool MoveCommand::checkHasNeighbour(Node * node, DIRECTION direction)
{
	return node->HasConnection(direction);
}

bool MoveCommand::checkIsWalkable(Node * node)
{
	return node->GetIsWalkable();
}


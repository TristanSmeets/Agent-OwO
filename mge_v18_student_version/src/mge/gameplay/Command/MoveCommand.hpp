#pragma once

#include "mge/gameplay/Command\Command.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Input/BoxInput.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/Audio/AudioLocator.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class MoveCommand : public Command
{
public:
	MoveCommand(MovableBehaviour& movable);
	virtual ~MoveCommand();
	void Execute();
	virtual void BoxMovement() = 0;
	virtual void PlayerMovement() = 0;
protected:
	void moveObject(Node* current, DIRECTION direction);
	void nodeBoxCheck(Node* current, DIRECTION direction);
	bool checkHasNeighbour(Node* node, DIRECTION direction);
	bool checkIsWalkable(Node* node);
	GeneralEvent* createMovedEvent();
	MovableBehaviour& movableObject;
	lua_State* luaAudio;
};

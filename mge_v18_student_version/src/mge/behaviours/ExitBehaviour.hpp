#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/Observer.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class ExitBehaviour : public AbstractBehaviour, public Observer
{
public:
	ExitBehaviour(unsigned int switches);
	virtual ~ExitBehaviour();
	void update(float pStep);
	void OnNotify(const EventInfo& info);
	void SubscribeToSubjects(std::vector<GameObject*> switchObjects);
	void SetPreviousType(NODETYPE nodeType);
	void SetExitNode(Node* node);

private:
	void checkNode();
	Node* exitNode;
	NODETYPE previousType;
	std::vector<GameObject*> subjects;
	int activatedSwitches = 0;
	int amountOfSwitches;
};
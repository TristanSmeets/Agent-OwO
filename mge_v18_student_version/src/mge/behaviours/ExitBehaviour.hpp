#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/Observer.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/util/EventQueue/EventStructs.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class ExitBehaviour : public AbstractBehaviour, public Observer<SwitchEvent>
{
public:
	ExitBehaviour(unsigned int switches);
	virtual ~ExitBehaviour();
	void update(float pStep);
	void OnNotify(const SwitchEvent& info);
	void SubscribeToSubjects(std::vector<GameObject*> switchObjects);
	void SetPreviousType(NODETYPE nodeType);
	void SetExitNode(Node* node);
	void UnsubscribeFromSubjects();

private:
	void checkNode();
	Node* exitNode;
	NODETYPE previousType;
	std::vector<GameObject*> subjects;
	int activatedSwitches = 0;
	int amountOfSwitches;
};
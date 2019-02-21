#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/Subject.hpp"
#include "mge/gameplay/Node.hpp"

class SwitchBehaviour : public AbstractBehaviour, Subject
{
public:
	SwitchBehaviour(Node& node);
	virtual ~SwitchBehaviour();
	void SetSwitchNode(Node& node);
	void update(float pStep);

private:
	void checkNodeType();
	Node& switchNode;
	NODETYPE previousType;
};
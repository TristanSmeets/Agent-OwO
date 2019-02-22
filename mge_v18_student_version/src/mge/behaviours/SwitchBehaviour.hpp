#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/Subject.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/util/EventQueue/EventStructs.hpp"

class SwitchBehaviour : public AbstractBehaviour, public Subject<SwitchEvent>
{
public:
	SwitchBehaviour(Node& node);
	virtual ~SwitchBehaviour();
	void SetSwitchNode(Node& node);
	void update(float pStep);

private:
	void checkNode();
	Node& switchNode;
	NODETYPE previousType;
};
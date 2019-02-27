#include "SwitchBehaviour.hpp"

SwitchBehaviour::SwitchBehaviour(Node& node) : AbstractBehaviour(), Subject(), switchNode(node)
{
	std::cout << "Creating SwitchBehaviour\n";
	previousType = node.GetNodeType();
}

SwitchBehaviour::~SwitchBehaviour()
{
	std::cout << "GC running on:SwitchBehaviour\n";
	//AbstractBehaviour::~AbstractBehaviour();
	//Subject::~Subject();
}

void SwitchBehaviour::SetSwitchNode(Node& node)
{
	switchNode = node;
}

void SwitchBehaviour::update(float pStep)
{
	checkNode();
}

void SwitchBehaviour::checkNode()
{
	if (previousType != switchNode.GetNodeType() &&
		switchNode.GetNodeType() != NODETYPE::GENERIC &&
		previousType != NODETYPE::GENERIC)
	{
		SwitchEvent info = SwitchEvent();
		switch (switchNode.GetNodeType())
		{
		case NODETYPE::BOX:
			info.activateSwitch = 1;
			break;
		case NODETYPE::SWITCH:
			info.activateSwitch = -1;
			break;
		default:
			info.activateSwitch = 0;
			break;
		}
		notify(info);
		previousType = switchNode.GetNodeType();
	}
}

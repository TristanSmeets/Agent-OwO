#include "SwitchBehaviour.hpp"

SwitchBehaviour::SwitchBehaviour() : AbstractBehaviour(), Subject()
{
	std::cout << "Creating SwitchBehaviour\n";
}

SwitchBehaviour::~SwitchBehaviour()
{
	std::cout << "GC running on:SwitchBehaviour\n";
	AbstractBehaviour::~AbstractBehaviour();
	Subject::~Subject();
	switchNode = nullptr;
}

void SwitchBehaviour::SetSwitchNode(Node* node)
{
	switchNode = node;
}

void SwitchBehaviour::update(float pStep)
{
	checkNodeType();
}

void SwitchBehaviour::checkNodeType()
{
	if (previousType != switchNode->GetNodeType())
	{
		std::cout << "Switch NodeType got changed.\n";
		EventInfo info = EventInfo();
		switch (switchNode->GetNodeType())
		{
		case NODETYPE::BOX:
			info.activeSwitch = 1;
			break;
		case NODETYPE::SWITCH:
			info.activeSwitch = -1;
			break;
		}
		notify(info);
	}
}

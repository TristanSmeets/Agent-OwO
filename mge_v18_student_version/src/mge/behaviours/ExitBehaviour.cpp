#include "ExitBehaviour.hpp"
#include "mge/core/Subject.hpp"

ExitBehaviour::ExitBehaviour(unsigned int switches) : 
	AbstractBehaviour(), Observer<SwitchEvent>(), amountOfSwitches(switches)
{
}

ExitBehaviour::~ExitBehaviour()
{
	std::cout << "GC running on:ExitBehaviour\n";
	
	//Unsubcribing from subjects
	for (unsigned int index = 0; index < subjects.size(); ++index)
	{
		Subject<SwitchEvent>* subject = dynamic_cast<Subject<SwitchEvent>*>(subjects[index]->getBehaviour());
		subject->RemoveObserver(this);
		subjects[index] = nullptr;
	}
	subjects.clear();
}

void ExitBehaviour::update(float pStep)
{
	checkNode();
}

void ExitBehaviour::OnNotify(const SwitchEvent & info)
{
	activatedSwitches += info.activateSwitch;
	exitNode->SetIsOpen(amountOfSwitches == activatedSwitches);
}

void ExitBehaviour::SubscribeToSubjects(std::vector<GameObject*> switchObjects)
{
	for (unsigned int index = 0; index < switchObjects.size(); ++index)
	{
		Subject<SwitchEvent>* subject = dynamic_cast<Subject<SwitchEvent>*>(switchObjects[index]->getBehaviour());
		subject->AddObserver(this);
	}
}

void ExitBehaviour::SetPreviousType(NODETYPE nodeType)
{
	previousType = nodeType;
}

void ExitBehaviour::SetExitNode(Node* node)
{
	exitNode = node;
	exitNode->SetIsOpen(activatedSwitches == amountOfSwitches);
}

void ExitBehaviour::checkNode()
{
	if (previousType != exitNode->GetNodeType())
	{
		std::cout << "EXIT reached!\n";
		previousType = exitNode->GetNodeType();
	}
}

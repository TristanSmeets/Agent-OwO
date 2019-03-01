#include "ExitBehaviour.hpp"
#include "mge/core/Subject.hpp"

ExitBehaviour::ExitBehaviour(unsigned int switches) : 
	AbstractBehaviour(), Observer<SwitchEvent>(), amountOfSwitches(switches)
{
	std::cout << "Creating new ExitBehaviour.\n";
}

ExitBehaviour::~ExitBehaviour()
{
	std::cout << "GC running on:ExitBehaviour\n";
	
	//Unsubcribing from subjects
	UnsubscribeFromSubjects();
}

void ExitBehaviour::update(float pStep)
{
	checkNode();
}

void ExitBehaviour::OnNotify(const SwitchEvent & info)
{
	activatedSwitches += info.activateSwitch;

	/*std::cout << "Amount of Switches: " << amountOfSwitches << std::endl;
	std::cout << "Activated switches: " << activatedSwitches << std::endl;*/

	exitNode->SetIsOpen(amountOfSwitches == activatedSwitches);
}

void ExitBehaviour::SubscribeToSubjects(std::vector<GameObject*> switchObjects)
{
	subjects = switchObjects;
	amountOfSwitches = switchObjects.size();
	activatedSwitches = 0;
	exitNode->SetIsOpen(amountOfSwitches == activatedSwitches);

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
	std::cout << "Activated Switches: " << activatedSwitches << std::endl;
	std::cout << "Amount of Switches: " << amountOfSwitches << std::endl;
	std::cout << "Exit is Open: " << (activatedSwitches == amountOfSwitches) << std::endl;
	exitNode->SetIsOpen(activatedSwitches == amountOfSwitches);
}

void ExitBehaviour::checkNode()
{
	if (previousType != exitNode->GetNodeType() &&
		exitNode->GetNodeType() == NODETYPE::GENERIC)
	{
		std::cout << "EXIT reached!\n";
		GeneralEvent info = GeneralEvent();
		info.nextLevel = true;
		EventQueue::QueueEvent(info);
		previousType = exitNode->GetNodeType();
	}
}

void ExitBehaviour::UnsubscribeFromSubjects()
{
	for (unsigned int index = 0; index < subjects.size(); ++index)
	{
		std::cout << "Unsubcribe ExitBehaviour from Switch\n";
		Subject<SwitchEvent>* subject = dynamic_cast<Subject<SwitchEvent>*>(subjects[index]->getBehaviour());
		subject->RemoveObserver(this);
		subjects[index] = nullptr;
	}
	subjects.clear();
}
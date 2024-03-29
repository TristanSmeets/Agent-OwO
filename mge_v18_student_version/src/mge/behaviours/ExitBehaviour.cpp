#include "ExitBehaviour.hpp"
#include "mge/core/Subject.hpp"

ExitBehaviour::ExitBehaviour(unsigned int switches) : 
	AbstractBehaviour(), Observer<SwitchEvent>(), amountOfSwitches(switches)
{
}

ExitBehaviour::~ExitBehaviour()
{	
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
	exitNode->SetIsOpen(activatedSwitches == amountOfSwitches);
}

Node & ExitBehaviour::GetExitNode()
{
	return *exitNode;
}

void ExitBehaviour::checkNode()
{
	if (previousType != exitNode->GetNodeType() &&
		exitNode->GetNodeType() == NODETYPE::GENERIC)
	{
		lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
		float pitch = LuaWrapper::GetNumber<float>(luaAudio, "ExitPitch");
		AudioLocator::GetAudio()->GetSoundEffect(SFX_EXIT).SetPitch(pitch);
		AudioLocator::GetAudio()->PlaySoundEffect(SFX_EXIT);
		LuaWrapper::CloseLuaState(luaAudio);
		GeneralEvent info = GeneralEvent();
		info.showEndDialogue = true;
		EventQueue::QueueEvent(info);
		previousType = exitNode->GetNodeType();
	}
}

void ExitBehaviour::UnsubscribeFromSubjects()
{
	for (unsigned int index = 0; index < subjects.size(); ++index)
	{
		Subject<SwitchEvent>* subject = dynamic_cast<Subject<SwitchEvent>*>(subjects[index]->getBehaviour());
		subject->RemoveObserver(this);
		subjects[index] = nullptr;
	}
	subjects.clear();
}
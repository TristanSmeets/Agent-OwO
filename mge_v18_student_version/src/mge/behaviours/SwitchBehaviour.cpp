#include "SwitchBehaviour.hpp"

SwitchBehaviour::SwitchBehaviour(Node& node) : AbstractBehaviour(), Subject(), switchNode(node)
{
	previousType = node.GetNodeType();
	luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
}

SwitchBehaviour::~SwitchBehaviour()
{
	LuaWrapper::CloseLuaState(luaAudio);
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
		AudioLocator::GetAudio()->GetSoundEffect(SFX_SWITCH).SetPitch(LuaWrapper::GetNumber<float>(luaAudio, "SwitchPitch"));
		AudioLocator::GetAudio()->PlaySoundEffect(SFX_SWITCH);
		notify(info);
		previousType = switchNode.GetNodeType();
	}
}

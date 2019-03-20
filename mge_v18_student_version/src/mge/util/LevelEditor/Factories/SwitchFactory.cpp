#include "SwitchFactory.hpp"
#include "mge/gameplay/GameObjects/TileObject.hpp"
#include "mge/behaviours/SwitchBehaviour.hpp"
#include <iostream>

SwitchFactory::SwitchFactory() : AbstractFactory()
{
}

SwitchFactory::SwitchFactory(lua_State* config) : AbstractFactory()
{
	std::string switchFile = LuaWrapper::GetString(config, "Switch");
	luaSwitch = LuaWrapper::InitializeLuaState(switchFile);

	std::cout << "Loading Switch Mesh\n";
	mesh = getMesh(luaSwitch);
	std::cout << "Loading Switch TextureMaterial\n";
	material = getTextureMaterial(luaSwitch);
}

SwitchFactory::~SwitchFactory()
{
	std::cout << "GC running on:SwitchFactory\n";
	mesh = nullptr;
	delete material;
	behaviour = nullptr;
	LuaWrapper::CloseLuaState(luaSwitch);
}

GameObject* SwitchFactory::CreateGameObject(const std::string& name)
{
	std::cout << "Creating " << name << std::endl;
	TileObject* newSwitch = new TileObject(luaSwitch, name);
	newSwitch->GetNode()->SetNodeType(NODETYPE::SWITCH);
	newSwitch->GetNode()->SetStartType(NODETYPE::SWITCH);
	behaviour = new SwitchBehaviour((*newSwitch->GetNode()));
	addMesh(newSwitch);
	addMaterial(newSwitch);
	addBehaviour(newSwitch);
	return newSwitch;
}

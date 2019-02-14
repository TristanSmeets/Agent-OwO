#include "SwitchFactory.hpp"

#include <iostream>

SwitchFactory::SwitchFactory(lua_State* config)
{
	std::string switchFile = LuaWrapper::GetString(config, "Switch");
	lua_State* luaSwitch = LuaWrapper::InitializeLuaState(switchFile);

	std::cout << "Loading Switch Mesh\n";
	mesh = getMesh(luaSwitch);
	std::cout << "Loading Switch TextureMaterial\n";
	material = getTextureMaterial(luaSwitch);
	behaviour = new NullBehaviour();
	LuaWrapper::CloseLuaState(luaSwitch);
}

SwitchFactory::~SwitchFactory()
{
	std::cout << "GC running on:SwitchFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject * SwitchFactory::CreateGameObject(const std::string & name)
{
	GameObject* newSwitch = new GameObject(name);
	addMesh(newSwitch);
	addMaterial(newSwitch);
	addBehaviour(newSwitch);
	return newSwitch;
}

#include "StartFactory.hpp"

StartFactory::StartFactory() : AbstractFactory()
{
}

StartFactory::StartFactory(lua_State* config) : AbstractFactory()
{
	lua_State* luaStart = LuaWrapper::InitializeLuaState(
	LuaWrapper::GetString(config,"Start"));

	std::cout << "Loading Start Mesh\n";
	mesh = getMesh(luaStart);
	std::cout << "Loading Start TextureMaterial\n";
	material = getTextureMaterial(luaStart);
	behaviour = new NullBehaviour();
	LuaWrapper::CloseLuaState(luaStart);
}

StartFactory::~StartFactory()
{
	std::cout << "GC running on:StartFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject * StartFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	GameObject* newStart = new GameObject(name);
	addMesh(newStart);
	addMaterial(newStart);
	addBehaviour(newStart);
	return nullptr;
}


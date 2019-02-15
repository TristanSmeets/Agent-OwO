#include "ExitFactory.hpp"

ExitFactory::ExitFactory(lua_State* config) : AbstractFactory()
{
	std::string exitFile = LuaWrapper::GetString(config, "Exit");
	lua_State* luaExit = LuaWrapper::InitializeLuaState(exitFile);

	std::cout << "Loading Exit Mesh\n";
	mesh = getMesh(luaExit);
	std::cout << "Loading Exit TextureMaterial\n";
	material = getTextureMaterial(luaExit);
	behaviour = new NullBehaviour();
	LuaWrapper::CloseLuaState(luaExit);
}

ExitFactory::~ExitFactory()
{
	std::cout << "GC running on:ExitFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject * ExitFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating %s\n", name;
	GameObject* newExit = new GameObject(name);
	addMesh(newExit);
	addMaterial(newExit);
	addBehaviour(newExit);
	return newExit;
}
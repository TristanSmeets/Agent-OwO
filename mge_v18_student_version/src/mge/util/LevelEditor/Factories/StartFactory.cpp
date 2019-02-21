#include "StartFactory.hpp"

#include "mge/gameplay/GameObjects/TileObject.hpp"

StartFactory::StartFactory() : AbstractFactory()
{
}

StartFactory::StartFactory(lua_State* config) : AbstractFactory()
{
	luaStart = LuaWrapper::InitializeLuaState(
	LuaWrapper::GetString(config,"Start"));

	std::cout << "Loading Start Mesh\n";
	mesh = getMesh(luaStart);
	std::cout << "Loading Start TextureMaterial\n";
	material = getTextureMaterial(luaStart);
	behaviour = new NullBehaviour();
}

StartFactory::~StartFactory()
{
	std::cout << "GC running on:StartFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
	LuaWrapper::CloseLuaState(luaStart);
}

GameObject * StartFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	TileObject* newStart = new TileObject(luaStart, name);
	newStart->GetNode()->SetNodeType(NODETYPE::START);
	newStart->GetNode()->SetStartType(NODETYPE::START);
	addMesh(newStart);
	addMaterial(newStart);
	addBehaviour(newStart);
	return newStart;
}


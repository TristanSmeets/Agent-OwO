#include "StartFactory.hpp"

#include "mge/gameplay/GameObjects/TileObject.hpp"

StartFactory::StartFactory() : AbstractFactory()
{
}

StartFactory::StartFactory(lua_State* config) : AbstractFactory()
{
	luaStart = LuaWrapper::InitializeLuaState(
	LuaWrapper::GetString(config,"Start"));
	mesh = getMesh(luaStart);
	material = getTextureMaterial(luaStart);
	behaviour = nullptr;
}

StartFactory::~StartFactory()
{
	mesh = nullptr;
	delete material;
	LuaWrapper::CloseLuaState(luaStart);
}

GameObject * StartFactory::CreateGameObject(const std::string & name)
{
	TileObject* newStart = new TileObject(luaStart, name);
	newStart->GetNode()->SetNodeType(NODETYPE::START);
	newStart->GetNode()->SetStartType(NODETYPE::START);
	addMesh(newStart);
	addMaterial(newStart);
	return newStart;
}


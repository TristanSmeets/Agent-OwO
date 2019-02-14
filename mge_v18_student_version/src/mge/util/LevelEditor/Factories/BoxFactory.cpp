#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"

BoxFactory::BoxFactory(lua_State* config)
{
	std::string boxFile = LuaWrapper::GetString(config, "Box");
	lua_State* luaBox = LuaWrapper::InitializeLuaState(boxFile);

	std::cout << "Loading Box Mesh\n";
	mesh = getMesh(luaBox);
	std::cout << "Loading Box TextureMaterial\n";
	material = getTextureMaterial(luaBox);
	behaviour = new NullBehaviour();
	LuaWrapper::CloseLuaState(luaBox);
}

BoxFactory::~BoxFactory()
{
	std::cout << "GC running on:BoxFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}
#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

BoxFactory::BoxFactory()  : AbstractFactory()
{
}

BoxFactory::BoxFactory(lua_State* config)
{
	std::string boxFile = LuaWrapper::GetString(config, "Box");
	lua_State* luaBox = LuaWrapper::InitializeLuaState(boxFile);
	mesh = getMesh(luaBox);
	material = getTextureMaterial(luaBox);
	LuaWrapper::CloseLuaState(luaBox);
}

BoxFactory::~BoxFactory()
{
	mesh = nullptr;
	delete material;
	behaviour = nullptr;
}

GameObject* BoxFactory::CreateGameObject(const std::string &name)
{
	GameObject* newBox = new GameObject(name);
	addMesh(newBox);
	addMaterial(newBox);
	behaviour = new MovableBehaviour(MOVABLE_TYPE::BOX_OBJECT);
	addBehaviour(newBox);
	return newBox;
}

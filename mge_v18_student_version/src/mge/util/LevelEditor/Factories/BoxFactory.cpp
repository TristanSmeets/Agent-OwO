#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

BoxFactory::BoxFactory()  : AbstractFactory()
{
}

BoxFactory::BoxFactory(lua_State* config)
{
	std::string boxFile = LuaWrapper::GetString(config, "Box");
	lua_State* luaBox = LuaWrapper::InitializeLuaState(boxFile);

	std::cout << "\nLoading Box Mesh\n";
	mesh = getMesh(luaBox);
	std::cout << "Loading Box TextureMaterial\n";
	material = getTextureMaterial(luaBox);
	LuaWrapper::CloseLuaState(luaBox);
}

BoxFactory::~BoxFactory()
{
	std::cout << "GC running on:BoxFactory\n";
	mesh = nullptr;
	delete material;
	behaviour = nullptr;
}

GameObject* BoxFactory::CreateGameObject(const std::string &name)
{
	std::cout << "Creating " << name << std::endl;
	GameObject* newBox = new GameObject(name);
	addMesh(newBox);
	addMaterial(newBox);
	behaviour = new MovableBehaviour(MOVABLE_TYPE::BOX_OBJECT);
	addBehaviour(newBox);
	return newBox;
}

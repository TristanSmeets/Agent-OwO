#include "mge/util/LevelEditor/Factories/PlayerFactory.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

PlayerFactory::PlayerFactory() : AbstractFactory()
{
}

PlayerFactory::PlayerFactory(lua_State* config) : AbstractFactory()
{
	std::string playerFile = LuaWrapper::GetString(config, "Player");
	lua_State* luaPlayer = LuaWrapper::InitializeLuaState(playerFile);

	mesh = getMesh(luaPlayer);
	material = getTextureMaterial(luaPlayer);
	behaviour = new MovableBehaviour(MOVABLE_TYPE::PLAYER_OBJECT);
	LuaWrapper::CloseLuaState(luaPlayer);
}

PlayerFactory::~PlayerFactory()
{
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject* PlayerFactory::CreateGameObject(const std::string & name)
{
	GameObject* newPlayer = new GameObject(name);
	addMesh(newPlayer);
	addMaterial(newPlayer);
	addBehaviour(newPlayer);
	return newPlayer;
}

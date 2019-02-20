#include "mge/util/LevelEditor/Factories/PlayerFactory.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"

PlayerFactory::PlayerFactory() : AbstractFactory()
{
}

PlayerFactory::PlayerFactory(lua_State* config) : AbstractFactory()
{
	std::string playerFile = LuaWrapper::GetString(config, "Player");
	lua_State* luaPlayer = LuaWrapper::InitializeLuaState(playerFile);

	std::cout << "Loading Player Mesh\n";
	mesh = getMesh(luaPlayer);
	std::cout << "Loading Player TextureMaterial\n";
	material = getTextureMaterial(luaPlayer);
	behaviour = new MovableBehaviour(MOVABLE_TYPE::PLAYER_OBJECT);
	LuaWrapper::CloseLuaState(luaPlayer);
}

PlayerFactory::~PlayerFactory()
{
	std::cout << "GC running on:PlayerFactor\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
}

GameObject* PlayerFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	GameObject* newPlayer = new GameObject(name);
	addMesh(newPlayer);
	addMaterial(newPlayer);
	addBehaviour(newPlayer);
	return newPlayer;
}

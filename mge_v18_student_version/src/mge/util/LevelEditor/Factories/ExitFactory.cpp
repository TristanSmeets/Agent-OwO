#include "ExitFactory.hpp"

#include "mge/gameplay/GameObjects/TileObject.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"

ExitFactory::ExitFactory() : AbstractFactory()
{
}

ExitFactory::ExitFactory(lua_State* config) : AbstractFactory()
{
	std::string exitFile = LuaWrapper::GetString(config, "Exit");
	luaExit = LuaWrapper::InitializeLuaState(exitFile);

	std::cout << "Loading Exit Mesh\n";
	mesh = getMesh(luaExit);
	std::cout << "Loading Exit TextureMaterial\n";
	material = getTextureMaterial(luaExit);

	unsigned int levelNumber = LuaWrapper::GetNumber<int>(config, "LevelToLoad");

	lua_State* levelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");

	lua_getglobal(levelInfo, "Switches");
	int switches = LuaWrapper::GetTableNumber(levelInfo, "Level_" + std::to_string(levelNumber));
	std::cout << "\nAmount of Switches: " << switches << std::endl;
	behaviour = new ExitBehaviour(switches);

	LuaWrapper::CloseLuaState(levelInfo);
}

ExitFactory::~ExitFactory()
{
	std::cout << "GC running on:ExitFactory\n";
	mesh = nullptr;
	delete material;
	delete behaviour;
	LuaWrapper::CloseLuaState(luaExit);
}

GameObject* ExitFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	TileObject* newExit = new TileObject(luaExit, name);
	newExit->GetNode()->SetNodeType(NODETYPE::EXIT);
	newExit->GetNode()->SetStartType(NODETYPE::EXIT);
	addMesh(newExit);
	addMaterial(newExit);
	addBehaviour(newExit);
	return newExit;
}
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
	mesh = getMesh(luaExit);
	material = getTextureMaterial(luaExit);
	luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
}

ExitFactory::~ExitFactory()
{
	mesh = nullptr;
	delete material;
	behaviour = nullptr;
	LuaWrapper::CloseLuaState(luaExit);
	LuaWrapper::CloseLuaState(luaLevelInfo);
}

GameObject* ExitFactory::CreateGameObject(const std::string & name)
{
	TileObject* newExit = new TileObject(luaExit, name);
	newExit->GetNode()->SetNodeType(NODETYPE::EXIT);
	newExit->GetNode()->SetStartType(NODETYPE::EXIT);
	
	lua_getglobal(luaLevelInfo, "Switches");
	switches = LuaWrapper::GetTableNumber(luaLevelInfo, "Level_" + std::to_string(levelNumber));
	behaviour = new ExitBehaviour(switches);
	ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(behaviour);
	exitBehaviour->SetExitNode(newExit->GetNode());
	exitBehaviour->SetPreviousType(NODETYPE::EXIT);
	addMesh(newExit);
	addMaterial(newExit);
	addBehaviour(newExit);
	return newExit;
}

#include "Level.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"

Level::Level(World * world, Camera* camera) :
world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	objectCreator = new ObjectCreator(config, world, camera);
}

Level::~Level()
{
	std::cout << "GC running on:Level.\n";

	if (objectCreator->GetTileObjects().size() > 0)
		UnloadLevel();
	delete objectCreator;
	LuaWrapper::CloseLuaState(config);
}

void Level::CreateLevel(int levelNumber)
{
	stepTracker = new StepTracker(levelNumber);
	objectCreator->SetRandomSeed(levelNumber);
	//Open the lua file.
	std::string filePath = "LuaGameScripts/Level/Level_" + std::to_string(levelNumber) + ".lua";
	luaLevel = LuaWrapper::InitializeLuaState(filePath);

	//Get table from luaFile and put it on the stack at -1
	lua_getglobal(luaLevel, "GameObjects");

	//Looping over the entire table
	lua_pushnil(luaLevel);
	while (lua_next(luaLevel, -2) != 0)
	{
		//uses 'key' (at index -2) and 'value' (at index -1) 
		std::string typeString = LuaWrapper::GetTableString(luaLevel, "Type");
		glm::vec3 position = LuaWrapper::GetTableVec3(luaLevel, "Position");
		glm::quat rotation = LuaWrapper::GetTableQuat(luaLevel, "Rotation");
		glm::vec3 scale = LuaWrapper::GetTableVec3(luaLevel, "Scale");

		objectCreator->CreateGameObject(typeString, position, rotation, scale);
		//Removes 'value'. keeps 'key' for next iteration
		lua_pop(luaLevel, 1);
	}
	lua_pop(luaLevel, 1);

	TileObject::CreateNodeConnections(objectCreator->GetTileObjects());
	objectCreator->ConfigureBehaviourStartNodes();
}

void Level::Resetlevel()
{
	TileObject::ResetNodes(objectCreator->GetTileObjects());
	objectCreator->ResetMovableObjects();
}

void Level::UnloadLevel()
{
	glm::vec3 offScreenPosition = glm::vec3(10, 10, 10);
	std::vector<GameObject*>& boxObjects = objectCreator->GetBoxObjects();
	std::vector<TileObject*>& tiles = objectCreator->GetTileObjects();

	GameObject* exit = objectCreator->GetExit();
	delete dynamic_cast<ExitBehaviour*>(exit->getBehaviour());
	std::vector<GameObject*>& switches = objectCreator->GetSwitchObjects();
	for (unsigned int index = 0; index < switches.size(); ++index)
	{
		delete switches[index]->getBehaviour();
		switches[index] = nullptr;
	}
	switches.clear();
	for (unsigned int index = 0; index < boxObjects.size(); ++index)
	{
		delete boxObjects[index]->getBehaviour();
		world->remove(boxObjects[index]);
		delete boxObjects[index];
	}
	boxObjects.clear();

	for (unsigned int index = 0; index < tiles.size(); ++index)
	{
		world->remove(tiles[index]);
		delete tiles[index];
	}
	tiles.clear();

	world->remove(objectCreator->GetPlayer());
	delete objectCreator->GetPlayer();
	delete stepTracker;
	LuaWrapper::CloseLuaState(luaLevel);
}

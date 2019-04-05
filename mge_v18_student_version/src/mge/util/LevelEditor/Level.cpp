#include "Level.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"

Level::Level(World * world, Camera* camera) :
world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua")),
objectCreator(ObjectCreator(config, world, camera))
{
}

Level::~Level()
{

	if (objectCreator.GetTileObjects().size() > 0)
		UnloadLevel();
	LuaWrapper::CloseLuaState(config);
}

void Level::CreateLevel(int levelNumber)
{
	stepTracker = new StepTracker(levelNumber);
	objectCreator.SetRandomSeed(levelNumber);

	heartbeatSFX = new GameObject("HEARTBEATSFX");
	heartbeatBehaviour = new HeartbeatBehaviour(levelNumber);
	heartbeatSFX->setBehaviour(heartbeatBehaviour);
	world->add(heartbeatSFX);

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

		objectCreator.CreateGameObject(typeString, position, rotation, scale);
		//Removes 'value'. keeps 'key' for next iteration
		lua_pop(luaLevel, 1);
	}
	lua_pop(luaLevel, 1);

	TileObject::CreateNodeConnections(objectCreator.GetTileObjects());
	objectCreator.ConfigureBehaviourStartNodes();

	if (AudioLocator::GetAudio()->GetMusicType() != MusicType::INGAME)
	{
		lua_State* luaAudio = LuaWrapper::InitializeLuaState("LuaGameScripts/Audio.lua");
		std::string filePath = LuaWrapper::GetString(luaAudio, "InGameBG");
		float pitch = LuaWrapper::GetNumber<float>(luaAudio, "InGamePitch");
		float volume = LuaWrapper::GetNumber<float>(luaAudio, "InGameVolume");
		AudioLocator::GetAudio()->StopMusic();
		AudioLocator::GetAudio()->SetMusicPitch(pitch);
		AudioLocator::GetAudio()->SetMusicVolume(volume);
		AudioLocator::GetAudio()->SetMusicType(MusicType::INGAME);
		AudioLocator::GetAudio()->PlayMusic(filePath);
	}
}

void Level::Resetlevel()
{
	TileObject::ResetNodes(objectCreator.GetTileObjects());
	objectCreator.ResetMovableObjects();
}

void Level::UnloadLevel()
{
	std::vector<GameObject*>& boxObjects = objectCreator.GetBoxObjects();
	std::vector<TileObject*>& tiles = objectCreator.GetTileObjects();

	GameObject* exit = objectCreator.GetExit();
	delete dynamic_cast<ExitBehaviour*>(exit->getBehaviour());
	std::vector<GameObject*>& switches = objectCreator.GetSwitchObjects();
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

	if (heartbeatBehaviour != nullptr)
	{
		delete heartbeatBehaviour;
		world->remove(heartbeatSFX);
		delete heartbeatSFX;
		heartbeatSFX = nullptr;
	}

	world->remove(objectCreator.GetPlayer());
	delete objectCreator.GetPlayer();
	delete stepTracker;
	LuaWrapper::CloseLuaState(luaLevel);
}

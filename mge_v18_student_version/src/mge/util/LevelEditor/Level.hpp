#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/core/World.hpp"
#include "mge/util/LevelEditor/ObjectCreator.hpp"
#include "mge/gameplay/StepTracker.hpp"
#include "mge/Audio/AudioLocator.hpp"
#include "mge/behaviours/HeartbeatBehaviour.hpp"
#include "glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>

/*	Class that will be responsible for setting up the level.
	Reads a lua file with gameobjects specified in it.
	Calls on a factory to create the gameobjects.
	Places the gameobjects it gets from the factory in the right position
*/
class Level
{
public:
	Level(World* world, Camera* camera);
	~Level();
	void CreateLevel(int levelNumber);
	void Resetlevel();
	void UnloadLevel();

private:
	World* world;
	lua_State* config;
	lua_State* luaLevel;
	StepTracker* stepTracker;
	ObjectCreator* objectCreator;
	GameObject* heartbeatSFX = nullptr;
	HeartbeatBehaviour* heartbeatBehaviour;
};

#endif // !LEVEL_HPP


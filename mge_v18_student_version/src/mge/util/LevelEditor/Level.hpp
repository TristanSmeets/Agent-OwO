#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/core/World.hpp"
#include "mge/util/LevelEditor/ObjectCreator.hpp"
#include "mge/gameplay/StepTracker.hpp"
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
	Level(World* world);
	~Level();
	void CreateLevel(int levelNumber);
private:
	World* world;
	lua_State* config;
	StepTracker* stepTracker;
	ObjectCreator* objectCreator;
};

#endif // !LEVEL_HPP


#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/core/World.hpp"
#include "mge/gameplay/Node.hpp"
#include "glm.hpp"
#include "mge/gameplay/StepTracker.hpp"
#include <vector>
#include <string>
#include "mge/util/LevelEditor/ObjectCreator.hpp"

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
	void CreateNodeConnections();
	void SetBehaviourStartNodes();
private:
	Node* getStartNode();
	Node* getNodeAtPosition(const glm::vec3& position);

	World* world;
	lua_State* config;
	StepTracker* stepTracker;
	ObjectCreator* objectCreator;
};

#endif // !LEVEL_HPP


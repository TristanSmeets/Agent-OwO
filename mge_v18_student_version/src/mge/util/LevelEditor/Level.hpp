#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/util/LevelEditor/Factories/ExitFactory.hpp"
#include "mge/util/LevelEditor/Factories/PlayerFactory.hpp"
#include "mge/util/LevelEditor/Factories/StartFactory.hpp"
#include "mge/util/LevelEditor/Factories/SwitchFactory.hpp"
#include "mge/util/LevelEditor/Factories/TileFactory.hpp"
#include "mge/util/LevelEditor/TestFactory.hpp"
#include "mge/core/World.hpp"
#include "mge/gameplay/Node.hpp"
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
	void CreateLevel(const std::string& filePath);
	void CreateNodeConnections();
	void PutObjectsOnNodes();
private:
	Node* getNodeAtPosition(glm::vec3 position);

	World* world;
	lua_State* config;
	BoxFactory* boxFactory;
	CameraFactory* cameraFactory;
	ExitFactory* exitFactory;
	PlayerFactory* playerFactory;
	StartFactory* startFactory;
	SwitchFactory* switchFactory;
	TileFactory* tileFactory;
	TestFactory* testFactory;
	GameObject* player;
	std::vector<TileObject*> tileObjects;
};

#endif // !LEVEL_HPP


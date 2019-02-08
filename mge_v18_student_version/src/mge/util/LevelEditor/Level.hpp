#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/util/LevelEditor/GameObjectFactory.hpp"
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
	void SetFactory(AbstractFactory* factory);
	void CreateLevel(const std::string& filePath);
private:
	World* world;
	AbstractFactory* factory;
	std::vector<GameObject*> gameObjects;
};

#endif // !LEVEL_HPP


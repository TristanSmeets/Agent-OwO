#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/core/AbstractFactory.hpp"
#include "mge/core/World.hpp"
#include <string>
#include <map>

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
private:
	World* world;
	std::map<std::string, AbstractFactory*> factoryMap;
	lua_State* config;

};

#endif // !LEVEL_HPP


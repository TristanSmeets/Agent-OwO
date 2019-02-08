#include "Level.hpp"
#include <lua.hpp>
#include <string>

Level::Level(World * world) : world(world)
{
}

Level::~Level()
{
	std::cout << "Calling GC on:Level." << std::endl;
}

void Level::SetFactory(AbstractFactory * factory)
{
	this->factory = factory;
}

void Level::CreateLevel(const std::string & filePath)
{
	//Open the lua file.
	lua_State* lua = LuaWrapper::InitializeLuaState(filePath);

	//Get table size
	unsigned int tableSize = LuaWrapper::GetNumber<int>(lua, "TableSize");

	//Get table from luaFile and put it on the stack at -1
	std::cout << "Getting GameObjects table from lua" << std::endl;
	lua_getglobal(lua, "GameObjects");
	
	//Looping over the entire table
	lua_pushnil(lua);
	while (lua_next(lua, -2) != 0)
	{
		/*uses 'key' (at index -2) and 'value' (at index -1) */

		printf("%s - %s\n",
			lua_typename(lua, lua_type(lua, -2)),
			lua_typename(lua, lua_type(lua, -1)));

		std::cout << "Pushing 'Type' to stack\n";
		
		std::string typeString = LuaWrapper::GetTableKeyValue<std::string>(lua, "Type");
		std::cout << "Type: " << typeString << std::endl;

		/*
		GameObject* newGameObject = factory->CreateGameObject(typeString);

		newGameObject->setTransform();
		gameObjects.push_back(newGameObject);
		*/
		/*Removes 'value'. keeps 'key' for next iteration*/
		lua_pop(lua, 1);
	}
	lua_pop(lua, 1);
	std::cout << "Stack size: " << lua_gettop(lua) << std::endl;
}

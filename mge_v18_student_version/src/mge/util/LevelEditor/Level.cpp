#include "Level.hpp"
#include <lua.hpp>
#include <string>
#include "glm.hpp"
#include "mge/core/World.hpp"

Level::Level(World * world) : world(world)
{
}

Level::~Level()
{
	std::cout << "GC running on:Level." << std::endl;
	for (int index = gameObjects.size() - 1; index >= 0; index--)
	{
		delete gameObjects[index];
	}

	delete factory;
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

		/*printf("(-2) %s - (-1) %s - (-3)%s\n",
			lua_typename(lua, lua_type(lua, -2)),
			lua_typename(lua, lua_type(lua, -1)),
			lua_typename(lua, lua_type(lua, -3)));
*/

		std::string typeString = LuaWrapper::GetTableString(lua, "Type");
		glm::vec3 position = LuaWrapper::GetTableVec3(lua, "Position");
		glm::vec3 rotation = LuaWrapper::GetTableVec3(lua, "Rotation");
		glm::vec3 scale = LuaWrapper::GetTableVec3(lua, "Scale");
		std::cout << "\nType: " << typeString << std::endl;
		printf("Position: (%f, %f, %f)\n", position.x, position.y, position.z);
		printf("Rotation: (%f, %f, %f)\n", rotation.x, rotation.y, rotation.z);
		printf("Scale: (%f, %f, %f)\n", scale.x, scale.y, scale.z);

		GameObject* newGameObject = factory->CreateGameObject(typeString);
		glm::mat4 rotationMatrix = glm::eulerAngleXYZ(rotation.x, -rotation.y, -rotation.z);
		glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
		newGameObject->setTransform(translationMatrix * rotationMatrix);
		newGameObject->scale(scale);
		world->add(newGameObject);
		gameObjects.push_back(newGameObject);


		/*Removes 'value'. keeps 'key' for next iteration*/
		lua_pop(lua, 1);
	}
	lua_pop(lua, 1);
	std::cout << "Stack size: " << lua_gettop(lua) << std::endl;
}

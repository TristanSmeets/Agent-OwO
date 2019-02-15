#include "Level.hpp"
#include "glm.hpp"
#include "Factories/BoxFactory.hpp"
#include "Factories/CameraFactory.hpp"
#include "Factories/ExitFactory.hpp"
#include "Factories/PlayerFactory.hpp"
#include "Factories/SwitchFactory.hpp"
#include "Factories/TileFactory.hpp"
#include "mge/core/Camera.hpp"
#include "mge/util/LevelEditor/TestFactory.hpp"

Level::Level(World * world) : world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	std::cout << "Filling factoryMap\nAdding CameraFactory\n";
	factoryMap["CAMERA"] = new CameraFactory();
	std::cout << "Adding ExitFactory\n";
	factoryMap["EXIT"] = new TestFactory();
	std::cout << "Adding PlayerFactory\n";
	factoryMap["PLAYER"] = new TestFactory();
	std::cout << "Adding SwitchFactory\n";
	factoryMap["SWITCH"] = new TestFactory();
	std::cout << "Adding TileFactory\n";
	factoryMap["TILE"] = new TestFactory();
}

Level::~Level()
{
	std::cout << "GC running on:Level.\n";
	
	
	factoryMap.clear();
	LuaWrapper::CloseLuaState(config);
}

void Level::CreateLevel(const std::string & filePath)
{
	//Open the lua file.
	lua_State* lua = LuaWrapper::InitializeLuaState(filePath);

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

		GameObject* newGameObject = factoryMap[typeString]->CreateGameObject(typeString);
		glm::mat4 rotationMatrix = glm::eulerAngleXYZ(rotation.x, -rotation.y, -rotation.z);
		glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
		newGameObject->setTransform(translationMatrix * rotationMatrix);
		newGameObject->scale(scale);
		world->add(newGameObject);
		if ("CAMERA" == typeString)
			world->setMainCamera(dynamic_cast<Camera*>(newGameObject));

		/*Removes 'value'. keeps 'key' for next iteration*/
		lua_pop(lua, 1);
	}
	lua_pop(lua, 1);
	std::cout << "Stack size: " << lua_gettop(lua) << std::endl;
}

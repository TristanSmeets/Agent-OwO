#include "Level.hpp"
#include "glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/util/LevelEditor/Factories/ExitFactory.hpp"
#include "mge/util/LevelEditor/Factories/PlayerFactory.hpp"
#include "mge/util/LevelEditor/Factories/SwitchFactory.hpp"
#include "mge/util/LevelEditor/Factories/TileFactory.hpp"
#include "mge/core/Camera.hpp"
#include "mge/util/LevelEditor/TestFactory.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

Level::Level(World * world) : world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	boxFactory = new BoxFactory(config);
	cameraFactory = new CameraFactory();
	exitFactory = new ExitFactory(config);
	playerFactory = new PlayerFactory(config);
	startFactory = new StartFactory(config);
	switchFactory = new SwitchFactory(config);
	tileFactory = new TileFactory(config);
	testFactory = new TestFactory();
}

Level::~Level()
{
	std::cout << "GC running on:Level.\n";

	delete boxFactory;
	delete cameraFactory;
	delete exitFactory;
	delete playerFactory;
	delete startFactory;
	delete switchFactory;
	delete tileFactory;
	delete testFactory;

	LuaWrapper::CloseLuaState(config);
}

void Level::CreateLevel(const std::string & filePath)
{
	//Open the lua file.
	lua_State* lua = LuaWrapper::InitializeLuaState(filePath);
	//Get table from luaFile and put it on the stack at -1
	//std::cout << "Stack size: " << lua_gettop(lua) << std::endl;
	std::cout << "Getting GameObjects table from lua" << std::endl;
	lua_getglobal(lua, "GameObjects");

	//Looping over the entire table
	lua_pushnil(lua);
	while (lua_next(lua, -2) != 0)
	{
		//uses 'key' (at index -2) and 'value' (at index -1) 

		std::string typeString = LuaWrapper::GetTableString(lua, "Type");
		glm::vec3 position = LuaWrapper::GetTableVec3(lua, "Position");
		glm::quat rotation = LuaWrapper::GetTableQuat(lua, "Rotation");
		glm::vec3 scale = LuaWrapper::GetTableVec3(lua, "Scale");
		std::cout << "\nType: " << typeString << std::endl;
		printf("Position: (%f, %f, %f)\n", position.x, position.y, position.z);
		printf("Rotation: (%f, %f, %f, %f)\n", rotation.x, rotation.y, rotation.z, rotation.w);
		printf("Scale: (%f, %f, %f)\n", scale.x, scale.y, scale.z);

		GameObject* newGameObject;
		if ("BOX" == typeString)
			newGameObject = boxFactory->CreateGameObject(typeString);
		if ("CAMERA" == typeString)
			newGameObject = cameraFactory->CreateGameObject(typeString);
		if ("EXIT" == typeString)
			newGameObject = exitFactory->CreateGameObject(typeString);
		if ("PLAYER" == typeString)
			newGameObject = playerFactory->CreateGameObject(typeString);
		if ("SWITCH" == typeString)
			newGameObject = switchFactory->CreateGameObject(typeString);
		if ("START" == typeString)
			newGameObject = startFactory->CreateGameObject(typeString);
		if ("TILE" == typeString)
			newGameObject = tileFactory->CreateGameObject(typeString);

		glm::mat4 rotationMatrix = glm::toMat4(rotation);
		
		glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
		newGameObject->setTransform(translationMatrix * rotationMatrix);
		newGameObject->scale(scale);
		world->add(newGameObject);
		if ("CAMERA" == typeString)
		{
			newGameObject->setBehaviour(new KeysBehaviour());
			newGameObject->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
			world->setMainCamera(dynamic_cast<Camera*>(newGameObject));
		}
		//Removes 'value'. keeps 'key' for next iteration
		lua_pop(lua, 1);
	}
	lua_pop(lua, 1);
	std::cout << "Stack size: " << lua_gettop(lua) << std::endl;
}
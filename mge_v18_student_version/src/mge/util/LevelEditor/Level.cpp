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
#include "mge/behaviours/MovableBehaviour.hpp"

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

	std::cout << "Cleaning Nodes\n";
	for (int index = 0; index < nodes.size(); ++index)
	{
		delete nodes[index];
	}
	nodes.clear();
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
		{
			newGameObject = exitFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->GetNode()->SetPosition(position);
		}
		if ("PLAYER" == typeString)
		{
			newGameObject = playerFactory->CreateGameObject(typeString);
			player = newGameObject;
		}
		if ("SWITCH" == typeString)
		{
			newGameObject = switchFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->GetNode()->SetPosition(position);
		}
		if ("START" == typeString)
		{
			newGameObject = startFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->GetNode()->SetPosition(position);
		}
		if ("TILE" == typeString)
		{
			newGameObject = tileFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->GetNode()->SetPosition(position);
		}
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
	std::cout << "Nodes size: " << nodes.size() << std::endl;
	for (int index = 0; index < nodes.size(); ++index)
	{
		nodes[index]->CreateConnections(nodes, index);
		std::cout << "Amount of Connections: " << nodes[index]->GetConnectionCount() << std::endl;
	}
}

void Level::PutObjectsOnNodes()
{
	MovableBehaviour* movable = dynamic_cast<MovableBehaviour*>(player->getBehaviour());
	movable->SetCurrentNode(getNodeAtPosition(player->getLocalPosition()));
}

Node * Level::getNodeAtPosition(glm::vec3 position)
{
	for (int index = 0; index < nodes.size(); ++index)
	{
		glm::vec3 nodePosition = nodes[index]->GetPosition();

		if (position.x == nodePosition.x &&
			position.y == nodePosition.y &&
			position.z == nodePosition.z)
			return nodes[index];
		else
			return nullptr;
	}
}


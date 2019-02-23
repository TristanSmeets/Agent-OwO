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
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"

Level::Level(World * world) : world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	boxFactory = new BoxFactory(config);
	cameraFactory = new CameraFactory();
	exitFactory = new ExitFactory(config);
	playerFactory = new PlayerFactory(config);
	startFactory = new StartFactory(config);
	switchFactory = new SwitchFactory(config);
	tileFactory = new TileFactory(config);
}

Level::~Level()
{
	std::cout << "GC running on:Level.\n";
	
	delete stepTracker;
	delete boxFactory;
	delete cameraFactory;
	delete exitFactory;
	delete playerFactory;
	delete startFactory;
	delete switchFactory;
	delete tileFactory;

	std::cout << "\nCleaning TileObjects\n";
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		tileObjects[index] = nullptr;
	}
	tileObjects.clear();

	std::cout << "\nCleaning BoxObjects\n";
	for (unsigned int index = 0; index < boxObjects.size(); ++index)
	{
		delete boxObjects[index]->getBehaviour();
		boxObjects[index] = nullptr;
	}
	boxObjects.clear();

	std::cout << "\nCleaning SwitchObjects\n";
	for (unsigned int index = 0; index < switchObjects.size(); ++index)
	{
		delete switchObjects[index]->getBehaviour();
		switchObjects[index] = nullptr;
	}
	switchObjects.clear();

	player = nullptr;
	exitObject = nullptr;

	LuaWrapper::CloseLuaState(config);
}

void Level::CreateLevel(int levelNumber)
{
	stepTracker = new StepTracker(levelNumber);

	//Open the lua file.
	std::string filePath = "LuaGameScripts/Level/Level_" + std::to_string(levelNumber) + ".lua";
	lua_State* lua = LuaWrapper::InitializeLuaState(filePath);
	
	//Get table from luaFile and put it on the stack at -1
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
		/*std::cout << "\nType: " << typeString << std::endl;
		printf("Position: (%f, %f, %f)\n", position.x, position.y, position.z);
		printf("Rotation: (%f, %f, %f, %f)\n", rotation.x, rotation.y, rotation.z, rotation.w);
		printf("Scale: (%f, %f, %f)\n", scale.x, scale.y, scale.z);*/

		GameObject* newGameObject;
		if ("BOX" == typeString)
		{
			newGameObject = boxFactory->CreateGameObject(typeString);
			boxObjects.push_back(newGameObject);
		}
		if ("CAMERA" == typeString)
			newGameObject = cameraFactory->CreateGameObject(typeString);
		if ("EXIT" == typeString) 
		{
			newGameObject = exitFactory->CreateGameObject(typeString);
			TileObject* tileObject = dynamic_cast<TileObject*>(newGameObject);
			tileObject->SetNodePosition(position);
			tileObjects.push_back(tileObject);
			ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(newGameObject->getBehaviour());
			exitBehaviour->SetExitNode(tileObject->GetNode());
			exitBehaviour->SetPreviousType(NODETYPE::EXIT);
			exitObject = newGameObject;
		}
		if ("PLAYER" == typeString)
		{
			newGameObject = playerFactory->CreateGameObject(typeString);
			player = newGameObject;
		}
		if ("SWITCH" == typeString)
		{
			newGameObject = switchFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
			tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));
			switchObjects.push_back(newGameObject);
		}
		if ("START" == typeString)
		{
			newGameObject = startFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
			tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));

		}
		if ("TILE" == typeString)
		{
			newGameObject = tileFactory->CreateGameObject(typeString);
			dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
			tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));
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
	CreateNodeConnections();
}

void Level::CreateNodeConnections()
{
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		tileObjects[index]->CreateNodeConnections(tileObjects, index);
		std::cout << "Amount of Connections: " << tileObjects[index]->GetNode()->GetConnectionCount() << std::endl << std::endl;
	}
}

void Level::SetBehaviourStartNodes()
{
	MovableBehaviour* playerBehaviour = dynamic_cast<MovableBehaviour*>(player->getBehaviour());
	Node* startNode = getStartNode();
	playerBehaviour->SetCurrentNode(startNode);
	player->setLocalPosition(startNode->GetPosition());

	ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(exitObject->getBehaviour());
	exitBehaviour->SubscribeToSubjects(switchObjects);

	for (unsigned int index = 0; index < boxObjects.size(); ++index)
	{
		Node* boxNode = getNodeAtPosition(boxObjects[index]->getLocalPosition());
		boxNode->SetNodeType(NODETYPE::BOX);
		boxNode->SetCurrentGameObject(boxObjects[index]);

		MovableBehaviour* boxBehaviour = dynamic_cast<MovableBehaviour*>(boxObjects[index]->getBehaviour());
		boxBehaviour->SetCurrentNode(boxNode);
		boxObjects[index]->setLocalPosition(boxNode->GetPosition());
	}
}

Node * Level::getStartNode()
{
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		if (tileObjects[index]->GetNode()->GetNodeType() == NODETYPE::START)
			return tileObjects[index]->GetNode();
	}
	return nullptr;
}

Node * Level::getNodeAtPosition(const glm::vec3 & position)
{
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		glm::vec3 nodePosition = tileObjects[index]->getLocalPosition();
		if (position.x == nodePosition.x &&
			position.y == nodePosition.y &&
			position.z == nodePosition.z)
			return tileObjects[index]->GetNode();
	}
	return nullptr;
}


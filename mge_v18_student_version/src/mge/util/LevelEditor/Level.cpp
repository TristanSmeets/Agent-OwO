#include "Level.hpp"
#include "glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"

Level::Level(World * world) :
	world(world), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
	objectCreator = new ObjectCreator(config, world);
}

Level::~Level()
{
	std::cout << "GC running on:Level.\n";
	delete stepTracker;
	delete objectCreator;
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

		objectCreator->CreateGameObject(typeString, position, rotation, scale);
		//Removes 'value'. keeps 'key' for next iteration
		lua_pop(lua, 1);
	}
	lua_pop(lua, 1);
	CreateNodeConnections();
}

void Level::CreateNodeConnections()
{
	std::vector<TileObject*> tileObjects = objectCreator->GetTileObjects();

	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		tileObjects[index]->CreateNodeConnections(tileObjects, index);
		std::cout << "Amount of Connections: " << tileObjects[index]->GetNode()->GetConnectionCount() << std::endl << std::endl;
	}
}

void Level::SetBehaviourStartNodes()
{
	GameObject* player = objectCreator->GetPlayer();
	MovableBehaviour* playerBehaviour = dynamic_cast<MovableBehaviour*>(player->getBehaviour());
	Node* startNode = getStartNode();
	playerBehaviour->SetCurrentNode(startNode);
	player->setLocalPosition(startNode->GetPosition());

	GameObject* exitObject = objectCreator->GetExit();
	ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(exitObject->getBehaviour());
	exitBehaviour->SubscribeToSubjects(objectCreator->GetSwitchObjects());

	std::vector<GameObject*> boxObjects = objectCreator->GetBoxObjects();

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
	std::vector<TileObject*> tileObjects = objectCreator->GetTileObjects();
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		if (tileObjects[index]->GetNode()->GetNodeType() == NODETYPE::START)
			return tileObjects[index]->GetNode();
	}
	return nullptr;
}

Node * Level::getNodeAtPosition(const glm::vec3 & position)
{
	std::vector<TileObject*> tileObjects = objectCreator->GetTileObjects();
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


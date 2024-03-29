#include "ObjectCreator.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

ObjectCreator::ObjectCreator(lua_State* config, World * world, Camera* camera) :
	config(config), world(world), cameraObject(camera)
{
	boxFactory = new BoxFactory(config);
	cameraFactory = new CameraFactory(config);
	exitFactory = new ExitFactory(config);
	playerFactory = new PlayerFactory(config);
	startFactory = new StartFactory(config);
	switchFactory = new SwitchFactory(config);
	tileFactory = new TileFactory(config);
}

ObjectCreator::~ObjectCreator()
{
	delete boxFactory;
	delete cameraFactory;
	delete exitFactory;
	delete playerFactory;
	delete startFactory;
	delete switchFactory;
	delete tileFactory;
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		tileObjects[index] = nullptr;
	}
	tileObjects.clear();

	for (unsigned int index = 0; index < boxObjects.size(); ++index)
	{
		boxObjects[index] = nullptr;
	}
	boxObjects.clear();

	for (unsigned int index = 0; index < switchObjects.size(); ++index)
	{
		switchObjects[index] = nullptr;
	}
	switchObjects.clear();

	playerObject = nullptr;
	exitObject = nullptr;
	cameraObject = nullptr;
}

void ObjectCreator::CreateGameObject(const std::string & objectType, const glm::vec3 & position, const glm::quat & rotation, const glm::vec3 & scale)
{
	GameObject* newGameObject;
	if ("BOX" == objectType)
	{
		newGameObject = boxFactory->CreateGameObject(objectType);
		boxObjects.push_back(newGameObject);
	}
	if ("CAMERA" == objectType)
	{
		if (cameraObject == nullptr)
		{
			newGameObject = cameraFactory->CreateGameObject(objectType);
			cameraObject = newGameObject;
		}
		else
			newGameObject = cameraObject;
	}
	if ("EXIT" == objectType)
	{
		newGameObject = exitFactory->CreateGameObject(objectType);
		addToTileObjectsandSetNode(newGameObject, position);
		exitObject = newGameObject;
	}
	if ("PLAYER" == objectType)
	{
		newGameObject = playerFactory->CreateGameObject(objectType);
		playerObject = newGameObject;
	}
	if ("SWITCH" == objectType)
	{
		newGameObject = switchFactory->CreateGameObject(objectType);
		addToTileObjectsandSetNode(newGameObject, position);
		switchObjects.push_back(newGameObject);
	}
	if ("START" == objectType)
	{
		newGameObject = startFactory->CreateGameObject(objectType);
		addToTileObjectsandSetNode(newGameObject, position);
	}
	if ("TILE" == objectType)
	{
		newGameObject = tileFactory->CreateGameObject(objectType);
		addToTileObjectsandSetNode(newGameObject, position);
	}
	glm::mat4 rotationMatrix = glm::toMat4(rotation);

	glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
	newGameObject->setTransform(translationMatrix * rotationMatrix);
	newGameObject->scale(scale);
	world->add(newGameObject);

	if ("CAMERA" == objectType)
	{
		newGameObject->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
		world->setMainCamera(dynamic_cast<Camera*>(newGameObject));
	}
}

void ObjectCreator::ConfigureBehaviourStartNodes()
{
	configurePlayer();
	dynamic_cast<ExitBehaviour*>(exitObject->getBehaviour())->SubscribeToSubjects(GetSwitchObjects());
	configureBoxes();
}

void ObjectCreator::ResetMovableObjects()
{
	configurePlayer();
	resetBoxes();
	resetExit();
}

void ObjectCreator::resetExit()
{
	ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(exitObject->getBehaviour());
	exitBehaviour->SetPreviousType(NODETYPE::EXIT);
	Node& node = exitBehaviour->GetExitNode();
	node.SetNodeType(NODETYPE::EXIT);
}

void ObjectCreator::SetRandomSeed(int seed)
{
	tileFactory->SetRandomSeed(seed);
}

void ObjectCreator::configureBoxes()
{
	std::vector<GameObject*> boxObjects = GetBoxObjects();
	for (unsigned int index = 0; index < boxObjects.size(); ++index)
	{
		GameObject* currentBox = boxObjects[index];

		Node* boxNode = TileObject::GetNodeAtPosition(
			GetTileObjects(),
			currentBox->getLocalPosition());
		boxNode->SetNodeType(NODETYPE::BOX);
		boxNode->SetCurrentGameObject(currentBox);

		dynamic_cast<MovableBehaviour*>(currentBox->getBehaviour())->SetCurrentNode(boxNode);
		currentBox->setLocalPosition(boxNode->GetPosition());
	}
	boxStartingNodes = TileObject::GetNodesOfType(GetTileObjects(), NODETYPE::BOX);
}

void ObjectCreator::configurePlayer()
{
	std::vector<Node*> playerNodes = TileObject::GetNodesOfType(GetTileObjects(), NODETYPE::START);
	Node* startNode = playerNodes[0];
	dynamic_cast<MovableBehaviour*>(playerObject->getBehaviour())->SetCurrentNode(startNode);
	playerObject->setLocalPosition(startNode->GetPosition());
}

void ObjectCreator::resetBoxes()
{
	std::vector<GameObject*> boxObjects = GetBoxObjects();

	for (unsigned int current = 0; current < boxObjects.size(); ++current)
	{
		Node* boxNode = boxStartingNodes[current];
		GameObject* boxObject = boxObjects[current];
		dynamic_cast<MovableBehaviour*>(boxObject->getBehaviour())->SetCurrentNode(boxNode);
		boxNode->SetNodeType(NODETYPE::BOX);
		boxNode->SetCurrentGameObject(boxObject);
		boxObject->setLocalPosition(boxNode->GetPosition());
	}
}

void ObjectCreator::addToTileObjectsandSetNode(GameObject * newGameObject, const glm::vec3 & position)
{
	dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
	tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));
}

std::vector<TileObject*>& ObjectCreator::GetTileObjects()
{
	return tileObjects;
}

std::vector<GameObject*>& ObjectCreator::GetBoxObjects()
{
	return boxObjects;
}

std::vector<GameObject*>& ObjectCreator::GetSwitchObjects()
{
	return switchObjects;
}

GameObject* ObjectCreator::GetPlayer()
{
	return playerObject;
}

GameObject* ObjectCreator::GetExit()
{
	return exitObject;
}


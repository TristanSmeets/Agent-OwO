#include "ObjectCreator.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/behaviours/ExitBehaviour.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

ObjectCreator::ObjectCreator(lua_State* config, World * world) : config(config), world(world)
{
	boxFactory = new BoxFactory(config);
	cameraFactory = new CameraFactory();
	exitFactory = new ExitFactory(config);
	playerFactory = new PlayerFactory(config);
	startFactory = new StartFactory(config);
	switchFactory = new SwitchFactory(config);
	tileFactory = new TileFactory(config);
}

ObjectCreator::~ObjectCreator()
{
	std::cout << "GC running on:ObjectCreator\n";
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

	playerObject = nullptr;
	exitObject = nullptr;
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
		newGameObject = cameraFactory->CreateGameObject(objectType);
	if ("EXIT" == objectType)
	{
		newGameObject = exitFactory->CreateGameObject(objectType);
		TileObject* tileObject = dynamic_cast<TileObject*>(newGameObject);
		tileObject->SetNodePosition(position);
		tileObjects.push_back(tileObject);
		ExitBehaviour* exitBehaviour = dynamic_cast<ExitBehaviour*>(newGameObject->getBehaviour());
		exitBehaviour->SetExitNode(tileObject->GetNode());
		exitBehaviour->SetPreviousType(NODETYPE::EXIT);
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
		dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
		tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));
		switchObjects.push_back(newGameObject);
	}
	if ("START" == objectType)
	{
		newGameObject = startFactory->CreateGameObject(objectType);
		dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
		tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));

	}
	if ("TILE" == objectType)
	{
		newGameObject = tileFactory->CreateGameObject(objectType);
		dynamic_cast<TileObject*>(newGameObject)->SetNodePosition(position);
		tileObjects.push_back(dynamic_cast<TileObject*>(newGameObject));
	}
	glm::mat4 rotationMatrix = glm::toMat4(rotation);

	glm::mat4 translationMatrix = glm::translate(glm::mat4(), position);
	newGameObject->setTransform(translationMatrix * rotationMatrix);
	newGameObject->scale(scale);
	world->add(newGameObject);

	if ("CAMERA" == objectType)
	{
		newGameObject->setBehaviour(new KeysBehaviour());
		newGameObject->rotate(glm::radians(180.0f), glm::vec3(0, 1, 0));
		world->setMainCamera(dynamic_cast<Camera*>(newGameObject));
	}
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
	// TODO: insert return statement here
	return switchObjects;
}

GameObject& ObjectCreator::GetPlayer()
{
	return *playerObject;
}

GameObject & ObjectCreator::GetExit()
{
	return *exitObject;
}


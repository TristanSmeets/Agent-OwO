#include <iostream>

#include "mge/util/LevelEditor/TestFactory.hpp"
#include "mge/config.hpp"

TestFactory::TestFactory()
{
	colourMaterial = new ColorMaterial(glm::vec3(0, 1, 0));
	cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
}

TestFactory::~TestFactory()
{
	std::cout << "Running GC on: TestFactory\n";
	delete colourMaterial;
	cubeMesh = nullptr;
}

GameObject * TestFactory::CreateGameObject(const std::string & objectType)
{
	GameObject* newGameObject = new GameObject(objectType, glm::vec3(0, 0, 0));
	GameObject* smallCube = new GameObject("SmallBox", glm::vec3(0, 3, 0));
	smallCube->setMesh(cubeMesh);
	smallCube->setMaterial(colourMaterial);
	smallCube->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	newGameObject->add(smallCube);
	newGameObject->setMesh(cubeMesh);
	newGameObject->setMaterial(colourMaterial);
	return newGameObject;
}

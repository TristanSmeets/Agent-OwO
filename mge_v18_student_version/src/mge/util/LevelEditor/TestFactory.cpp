#include <iostream>

#include "mge/util/LevelEditor/TestFactory.hpp"
#include "mge/core/Texture.hpp"
#include "mge/config.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

TestFactory::TestFactory() : AbstractFactory()
{
	lua_State* lua = LuaWrapper::InitializeLuaState("LuaGameScripts\\ModelViewer.lua");
	std::cout << "Creating ColorMaterial\n";
	colourMaterial = new ColorMaterial(glm::vec3(0, 1, 0));
	std::cout << "Creating TextureMaterial\n";
	textureMaterial = new TextureMaterial(Texture::load(LuaWrapper::GetString(lua, "DiffuseTexture")));
	std::cout << "Creating Mesh\n";
	cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	LuaWrapper::CloseLuaState(lua);
}

TestFactory::~TestFactory()
{
	std::cout << "Running GC on: TestFactory\n";
	delete colourMaterial;
	delete textureMaterial;
	cubeMesh = nullptr;
}

GameObject* TestFactory::CreateGameObject(const std::string& name)
{
	GameObject* newGameObject = new GameObject(name, glm::vec3(0, 0, 0));
	GameObject* smallCube = new GameObject("SmallBox", glm::vec3(0, 0, 3));
	smallCube->setMesh(cubeMesh);
	smallCube->setMaterial(colourMaterial);
	smallCube->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	newGameObject->add(smallCube);
	newGameObject->setMesh(cubeMesh);
	newGameObject->setMaterial(textureMaterial);
	return newGameObject;
}
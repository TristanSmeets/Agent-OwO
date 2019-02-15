#include <iostream>

#include "mge/util/LevelEditor/TestFactory.hpp"
#include "mge/core/Texture.hpp"
#include "mge/config.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

TestFactory::TestFactory() : AbstractFactory()
{
	lua_State* lua = LuaWrapper::InitializeLuaState("LuaGameScripts\\ModelViewer.lua");
	colourMaterial = new ColorMaterial(glm::vec3(0, 1, 0));
	textureMaterial = new TextureMaterial(Texture::load(LuaWrapper::GetString(lua, "DiffuseTexture")));
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

GameObject * TestFactory::CreateGameObject(const std::string& name)
{
	GameObject* newGameObject = new GameObject(name, glm::vec3(0, 0, 0));
	/*GameObject* smallCube = new GameObject("SmallBox", glm::vec3(0, 3, 0));
	smallCube->setMesh(cubeMesh);
	smallCube->setMaterial(colourMaterial);
	smallCube->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	newGameObject->add(smallCube);*/
	newGameObject->setMesh(cubeMesh);
	newGameObject->setMaterial(textureMaterial);
	return newGameObject;
}
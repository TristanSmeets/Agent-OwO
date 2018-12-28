#include <string>
#include <string>

#include "glm.hpp"
//Core
#include "mge/core/Renderer.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
//Materials
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
//Behaviours
#include "mge/behaviours/CameraOrbitBehaviour.hpp"

#include "mge/util/LuaWrapper.hpp"
#include "BrokenOBJ.hpp"
#include "mge/config.hpp"

BrokenOBJ::BrokenOBJ() :AbstractGame()
{}

BrokenOBJ::~BrokenOBJ()
{}

void BrokenOBJ::initialize()
{
	AbstractGame::initialize();
}

void BrokenOBJ::_initializeScene()
{
	lua_State *config = LuaWrapper::InitializeLuaState("config.lua");
	std::string& modelPath = LuaWrapper::GetString(config, "ModelToLoad");
	std::string& texturePath = LuaWrapper::GetString(config, "TextureToLoad");

	//Load Mesh
	Mesh* sphereObj = Mesh::load(modelPath);

	//Load Material
	//AbstractMaterial* texture = new TextureMaterial(Texture::load(texturePath));
	AbstractMaterial* texture = new WobbleMaterial(Texture::load(texturePath));

	//Scene Setup
	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("camera", glm::vec3(0, 0, 15));
	_world->add(camera);
	_world->setMainCamera(camera);

	std::cout << "Creating .obj" << std::endl;
	GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
	sphere->scale(glm::vec3(5, 5, 5));
	sphere->setMesh(sphereObj);
	sphere->setMaterial(texture);
	_world->add(sphere);

	//Adding orbit behaviour for camera
	camera->setBehaviour(new CameraOrbitBehaviour(20, 45, 1.0f, sphere, _window));

	LuaWrapper::CloseLuaState(config);
}

void BrokenOBJ::_render()
{
	AbstractGame::_render();
}

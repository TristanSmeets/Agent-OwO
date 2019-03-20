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
#include "mge/materials/TerrainMaterial.hpp"
//Behaviours
#include "mge/behaviours/RotatingBehaviour.hpp"

#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/config.hpp"
#include "TerrainScene.hpp"

TerrainScene::TerrainScene() : AbstractGame()
{
}

TerrainScene::~TerrainScene()
{
}

void TerrainScene::initialize()
{
	AbstractGame::initialize();
}

void TerrainScene::_initializeScene()
{
	std::cout << "Getting paths from config.lua" << std::endl;
	lua_State *config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");
	std::string& modelPath = LuaWrapper::GetString(config, "ObjToLoad");
	std::string& diffuse1Path = LuaWrapper::GetString(config, "diffuse1");
	std::string& diffuse2Path = LuaWrapper::GetString(config, "diffuse2");
	std::string& diffuse3Path = LuaWrapper::GetString(config, "diffuse3");
	std::string& diffuse4Path = LuaWrapper::GetString(config, "diffuse4");
	std::string& heightPath = LuaWrapper::GetString(config, "heightMap");
	std::string& splatPath = LuaWrapper::GetString(config, "splatMap");

	Mesh* planeObj = Mesh::load(modelPath);

	std::cout << "Creating TerrainTexture struct" << std::endl;
	//TerrainTexture struct
	TerrainTexture* terrainTexture = new TerrainTexture();
	terrainTexture->Diffuse1 = Texture::load(diffuse1Path);
	terrainTexture->Diffuse2 = Texture::load(diffuse2Path);
	terrainTexture->Diffuse3 = Texture::load(diffuse3Path);
	terrainTexture->Diffuse4 = Texture::load(diffuse4Path);
	terrainTexture->HeightMap = Texture::load(heightPath);
	terrainTexture->SplatMap = Texture::load(splatPath);

	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("Camera", glm::vec3(0, 2, 2));
	camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	std::cout << "Creating plane" << std::endl;
	GameObject* plane = new GameObject("Plane", glm::vec3(0, 0, 0));
	plane->setMesh(planeObj);
	plane->setMaterial(new TerrainMaterial(terrainTexture));
	plane->setBehaviour(new RotatingBehaviour());
	_world->add(plane);

}

void TerrainScene::render()
{
}

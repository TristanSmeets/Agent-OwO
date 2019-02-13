//std::cout
#include <iostream>
#include "glm.hpp"

//MGE Core
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"

//Behaviours
#include "mge/behaviours/CameraOrbitBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

//Materials
#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"

//Utils
#include "mge/util/DebugHud.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "DesignerScene.hpp"
#include "mge/config.hpp"
#include "mge/util/LevelEditor/Level.hpp"
#include "mge/util/LevelEditor/TestFactory.hpp"

DesignerScene::DesignerScene() : AbstractGame()
{
}

DesignerScene::~DesignerScene()
{
}

void DesignerScene::initialize()
{
	AbstractGame::initialize();
}

void DesignerScene::_initializeScene()
{
	//Initialize lua_State
	std::cout << "Initializing Lua file" << std::endl;
	lua_State* modelViewer = LuaWrapper::InitializeLuaState("LuaGameScripts\\ModelViewer.lua");
	
	/**/
	//Creating LightingData
	std::cout << "Creating LightingData." << std::endl;
	LightingData* lighting = new LightingData();
	
	std::cout << "Getting LightType" << std::endl;
	int lightType = LuaWrapper::GetNumber<int>(modelViewer, "LightType");
	std::cout << "LightType: " << lightType << std::endl;
	switch (lightType)
	{
	case 0:
		lighting->Type = LightType::DIRECTIONAL;
		break;
	case 1:
		lighting->Type = LightType::POINT;
		break;
	case 2:
		lighting->Type = LightType::SPOTLIGHT;
		break;
	default:
		lighting->Type = LightType::DIRECTIONAL;
		break;
	}
	std::cout << "Getting Ambient Colour" << std::endl;
	lighting->Ambient = glm::vec3(
		LuaWrapper::GetTableValue<float>(modelViewer, "Ambient", "red"),
		LuaWrapper::GetTableValue<float>(modelViewer,"Ambient", "green"),
		LuaWrapper::GetTableValue<float>(modelViewer,"Ambient", "blue")
	);
	std::cout << "Getting Diffuse Colour" << std::endl;
	lighting->Diffuse = glm::vec3(
		LuaWrapper::GetTableValue<float>(modelViewer, "Diffuse", "red"),
		LuaWrapper::GetTableValue<float>(modelViewer, "Diffuse", "green"),
		LuaWrapper::GetTableValue<float>(modelViewer, "Diffuse", "blue")
	);
	std::cout << "Getting Specular Colour" << std::endl;
	lighting->Specular = glm::vec3(
		LuaWrapper::GetTableValue<float>(modelViewer, "Specular", "red"),
		LuaWrapper::GetTableValue<float>(modelViewer, "Specular", "green"),
		LuaWrapper::GetTableValue<float>(modelViewer, "Specular", "blue")
	);
	lighting->Constant = LuaWrapper::GetNumber<float>(modelViewer, "Constant");
	lighting->Linear = LuaWrapper::GetNumber<float>(modelViewer, "Linear");
	lighting->Quadratic = LuaWrapper::GetNumber<float>(modelViewer, "Quadratic");
	lighting->CutOff =	LuaWrapper::GetNumber<float>(modelViewer, "CutOff");
	lighting->OuterCutOff = LuaWrapper::GetNumber<float>(modelViewer, "OuterCutOff");

	//Creating AbstractMaterial
	AbstractMaterial* colourMaterial = new ColorMaterial(lighting->Ambient);

	//Creating Material struct
	std::cout << "Creating Material" << std::endl;
	Material* material = new Material();
	material->DiffuseTexture = Texture::load(LuaWrapper::GetString(modelViewer, "DiffuseTexture"));
	material->SpecularTexture = Texture::load(LuaWrapper::GetString(modelViewer, "SpecularTexture"));
	material->ShininessFactor = LuaWrapper::GetNumber<int>(modelViewer, "ShininessFactor");

	//Creating AbstractMaterial
	std::cout << "Creating LitMaterial" << std::endl;
	AbstractMaterial* litMaterial = new LitMaterial(material);

	//Creating Mesh
	std::cout << "Creating Meshes" << std::endl;
	Mesh* objectMesh = Mesh::load(LuaWrapper::GetString(modelViewer, "ModelPath"));
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	/**/

	//Creating Camera
	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("Camera", glm::vec3(0, 5, 5));
	_world->add(camera);
	_world->setMainCamera(camera);

	/**/
	//Creating GameObject that will hold model
	std::cout << "Creating Model GameObject" << std::endl;
	GameObject* model = new GameObject("Model", glm::vec3(0, 0, 0));
	model->scale(glm::vec3(1, 1, 1));
	model->setMesh(objectMesh);
	model->setMaterial(litMaterial);
	_world->add(model);

	//Setting CameraOrbitBehavior
	camera->setBehaviour(new CameraOrbitBehaviour(
		LuaWrapper::GetNumber<float>(modelViewer, "CameraDistance"),
		89.0f,
		LuaWrapper::GetNumber<float>(modelViewer, "CameraMoveSpeed"),
		model, _window));
	/**/

	/**/
	//Creating Light
	std::cout << "Creating Light" << std::endl;
	Light* light = new Light("light", glm::vec3(2, 0, 0), lighting);
	light->setMesh(cubeMesh);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMaterial(colourMaterial);
	light->setBehaviour(new KeysBehaviour(40, 100));
	_world->add(light);
}

void DesignerScene::_render()
{
	AbstractGame::_render();
}


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
#include "mge/core/Light.hpp"
//Materials
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
//Behaviours
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/CameraOrbitBehaviour.hpp"

#include "TristanScene.h"
#include "mge/config.hpp"

TristanScene::TristanScene():AbstractGame()
{
}

TristanScene::~TristanScene()
{
}

void TristanScene::initialize()
{
	AbstractGame::initialize();
}

void TristanScene::_initializeScene()
{
	//Meshes
	Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
	Mesh* coneMeshS = Mesh::load(config::MGE_MODEL_PATH + "cone_smooth.obj");
	Mesh* suzannaMeshS = Mesh::load(config::MGE_MODEL_PATH + "suzanna_smooth.obj");

	//Materials
	//Create some materials to display the cube, the plane and the light
	AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
	AbstractMaterial* colourMaterial = new ColorMaterial(glm::vec3(0, 1, 0.9903f));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
	AbstractMaterial* bricksMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
	AbstractMaterial* landMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "land.jpg"));
	
	//Creating a Material for the litmaterial
	Material* material = new Material();
	material->DiffuseTexture = Texture::load(config::MGE_TEXTURE_PATH + "container2.png");
	material->SpecularTexture = Texture::load(config::MGE_TEXTURE_PATH + "container2_specular.png");
	material->ShininessFactor = 32;

	//Creating LightingData for the light
	LightingData* data = new LightingData();
	data->Type = LightType::SPOTLIGHT;
	data->Ambient = glm::vec3(1, 1, 1);
	data->Diffuse = glm::vec3(1, 1, 1);
	data->Specular = glm::vec3(1, 1, 1);
	data->Constant = 1.0f;
	data->Linear = 0.14f;
	data->Quadratic = 0.07f;
	data->CutOff = 12.5f;
	data->OuterCutOff = 15.5f;

	AbstractMaterial* litMaterial = new LitMaterial(material);

	//Scene setup

	//Add camera first(it will be updated last)
	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("camera", glm::vec3(0, 5, 5));
	camera->rotate(glm::radians(-45.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	//Add the floor with a landMaterial
	std::cout << "Creating Plane" << std::endl;
	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->scale(glm::vec3(5, 5, 5));
	plane->setMesh(planeMeshDefault);
	plane->setMaterial(runicStoneMaterial);
	_world->add(plane);

	//Add a monkey head with the runicStone Material
	std::cout << "Creating Suzanna" << std::endl;
	GameObject* suzanna = new GameObject("suzanna", glm::vec3(2, 2, 0));
	suzanna->scale(glm::vec3(1, 1, 1));
	suzanna->setMesh(suzannaMeshS);
	suzanna->setMaterial(litMaterial);
	//suzanna->setBehaviour(new RotatingBehaviour());
	_world->add(suzanna);

	std::cout << "Creating 2nd Suzanna" << std::endl;
	GameObject* suzanna2 = new GameObject("suzanna", glm::vec3(-2, 2, 0));
	suzanna2->setMesh(cubeMeshF);
	suzanna2->setMaterial(litMaterial);
	//suzanna2->setBehaviour(new RotatingBehaviour());
	_world->add(suzanna2);

	

	Light* light = new Light("light",						//Name
		glm::vec3(0, 2, 0),									//Position
		data);												//Lighting variables

	light->setMesh(cubeMeshF);
	light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->setMaterial(lightMaterial);
	light->setBehaviour(new KeysBehaviour(40,100));
	//light->setBehaviour(new CameraOrbitBehaviour(5, 45, 1, suzanna, _window));
	_world->add(light);

	

	//////Add a rotating brick sphere.
	//std::cout << "Creating Sphere" << std::endl;
	//GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
	//sphere->setMesh(sphereMeshS);
	//sphere->setMaterial(bricksMaterial);
	//sphere->setBehaviour(new RotatingBehaviour());
	//_world->add(sphere);

	////Add a yellow cone
	//std::cout << "Creating Cone" << std::endl;
	//GameObject* cone = new GameObject("Cone", glm::vec3(-5, -5, 0));
	//cone->scale(glm::vec3(2.5f, 2.5f, 2.5f));
	//cone->setMesh(coneMeshS);
	//cone->setMaterial(lightMaterial);
	//_world->add(cone);

	//camera->setBehaviour(new CameraOrbitBehaviour(5, 45.0f, 1.0f, suzanna, _window));

}

void TristanScene::_render()
{
	AbstractGame::_render();
}

#include "CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include <iostream>

CameraFactory::CameraFactory() : AbstractFactory()
{
	material = nullptr;
	mesh = nullptr;
	behaviour = new NullBehaviour();
}

CameraFactory::~CameraFactory()
{
	std::cout << "GC running on:CameraFactory\n";
	delete behaviour;
}

GameObject* CameraFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	return new Camera(name);//,
		//glm::vec3(0,0,0),
		//glm::orthoRH(0.0f,1280.0f,0.0f,720.0f,0.1f,100.0f));
}


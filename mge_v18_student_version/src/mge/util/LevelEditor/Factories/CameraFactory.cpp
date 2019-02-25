#include "CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include <iostream>

CameraFactory::CameraFactory() : AbstractFactory()
{
	material = nullptr;
	mesh = nullptr;
	behaviour = nullptr;

}

CameraFactory::~CameraFactory()
{
	std::cout << "GC running on:CameraFactory\n";
}

GameObject* CameraFactory::CreateGameObject(const std::string & name)
{
	std::cout << "Creating " << name << std::endl;
	return new Camera(name,
		glm::vec3(0, 0, 0),
		glm::ortho(-7.5f, 7.5f, -3.0f, 4.0f, 0.1f, 100.0f));
}


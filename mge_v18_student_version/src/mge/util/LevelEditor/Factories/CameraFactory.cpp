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
	std::cout << "Creating %s\n", name;
	return new Camera(name);
}


#include "CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include <iostream>

CameraFactory::CameraFactory()
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

GameObject * CameraFactory::CreateGameObject(const std::string & name)
{
	return new Camera(name);
}


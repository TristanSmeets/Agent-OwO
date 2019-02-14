#pragma once

#include "mge/core/AbstractFactory.hpp"

class CameraFactory : 
	public AbstractFactory
{
	CameraFactory();
	~CameraFactory();
	GameObject* CreateGameObject(const std::string& name);
};
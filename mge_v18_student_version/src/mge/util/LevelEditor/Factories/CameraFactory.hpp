#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class CameraFactory : 
	public AbstractFactory
{
public:
	CameraFactory();
	virtual ~CameraFactory();
	GameObject* CreateGameObject(const std::string& name);
};
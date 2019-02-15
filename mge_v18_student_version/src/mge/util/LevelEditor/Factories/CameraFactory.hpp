#pragma once

#include "mge/core/AbstractFactory.hpp"

class CameraFactory : 
	public AbstractFactory
{
public:
	CameraFactory();
	virtual ~CameraFactory();
	GameObject* CreateGameObject(const std::string& name);
};
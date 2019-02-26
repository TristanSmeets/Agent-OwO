#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class CameraFactory : 
	public AbstractFactory
{
public:
	CameraFactory(lua_State* config);
	virtual ~CameraFactory();
	GameObject* CreateGameObject(const std::string& name);

private:
	lua_State* config;
};
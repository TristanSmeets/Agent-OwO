#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class BoxFactory : 
	public AbstractFactory
{
public:
	BoxFactory();
	BoxFactory(lua_State* config);
	virtual ~BoxFactory();
	GameObject* CreateGameObject(const std::string& name);
};

#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"

class StartFactory : public AbstractFactory
{
public:
	StartFactory();
	StartFactory(lua_State* config);
	~StartFactory();
	GameObject* CreateGameObject(const std::string& name);
};

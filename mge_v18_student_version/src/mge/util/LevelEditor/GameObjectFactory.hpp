#pragma once

#include "mge/core/AbstractFactory.hpp"

class GameObjectFactory :
	public AbstractFactory
{
public:
	GameObjectFactory();
	virtual ~GameObjectFactory();
	GameObject* CreateGameObject(int objectType);
};


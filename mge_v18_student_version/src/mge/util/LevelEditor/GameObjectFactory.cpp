#include "GameObjectFactory.hpp"
#include <iostream>

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
	std::cout << "running GC on:GameObjectFactory." << std::endl;
}

GameObject * GameObjectFactory::CreateGameObject(int objectType)
{
	return nullptr;
}

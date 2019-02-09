#include "GameObjectFactory.hpp"
#include <iostream>

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
	std::cout << "running GC on:GameObjectFactory." << std::endl;
}

GameObject * GameObjectFactory::CreateGameObject(const std::string& objectType)
{
	return nullptr;
}

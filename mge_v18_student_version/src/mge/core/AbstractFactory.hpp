#ifndef ABSTRACTFACTORY_HPP
#define ABSTRACTFACTORY_HPP

#include "mge/core/GameObject.hpp"

class AbstractFactory
{
public:
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual GameObject* CreateGameObject(int objectType) = 0;
};

#endif // !ABSTRACTFACTORY_HPP

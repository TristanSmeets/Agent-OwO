#ifndef ABSTRACTFACTORY_HPP
#define ABSTRACTFACTORY_HPP

#include "mge/core/GameObject.hpp"

class AbstractFactory
{
public:
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual GameObject* CreateGameObject(const std::string& typeName) = 0;
protected:
	virtual void addMesh(GameObject* gameObject) = 0;
	virtual void AddTexture(GameObject* gameObject) = 0;
	virtual void addBehaviour(GameObject* gameObject) = 0;
};

#endif // !ABSTRACTFACTORY_HPP

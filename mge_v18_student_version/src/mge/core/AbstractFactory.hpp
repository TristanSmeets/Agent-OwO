#ifndef ABSTRACTFACTORY_HPP
#define ABSTRACTFACTORY_HPP

#include "mge/core/GameObject.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
//Because all classes that inherit will need access to lua files.
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class AbstractFactory
{
public:
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual GameObject* CreateGameObject(const std::string& name) = 0;
protected:
	virtual void addMesh(GameObject* gameObject) = 0;
	virtual void addMaterial(GameObject* gameObject) = 0;
	virtual void addBehaviour(GameObject* gameObject) = 0;
	AbstractMaterial* material;
	Mesh* mesh;
	AbstractBehaviour* behaviour;
};

#endif // !ABSTRACTFACTORY_HPP

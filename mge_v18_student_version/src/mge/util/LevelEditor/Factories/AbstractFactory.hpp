#ifndef ABSTRACTFACTORY_HPP
#define ABSTRACTFACTORY_HPP

#include "mge/core/GameObject.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/behaviours/NullBehaviour.hpp"
//Because all classes that inherit will need access to lua files.
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/behaviours/NullBehaviour.hpp"

class AbstractFactory
{
public:
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual GameObject* CreateGameObject(const std::string& name) = 0;
protected:
	virtual void addMesh(GameObject* gameObject);
	virtual void addMaterial(GameObject* gameObject);
	virtual void addBehaviour(GameObject* gameObject);
	Mesh* getMesh(lua_State* lua);
	TextureMaterial* getTextureMaterial(lua_State* lua);
	AbstractMaterial* material;
	Mesh* mesh;
	AbstractBehaviour* behaviour;
};

#endif // !ABSTRACTFACTORY_HPP

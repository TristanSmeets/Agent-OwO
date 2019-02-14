#include "AbstractFactory.hpp"



AbstractFactory::AbstractFactory()
{
}

AbstractFactory::~AbstractFactory()
{
}

void AbstractFactory::addMesh(GameObject * gameObject)
{
	gameObject->setMesh(mesh);
}

void AbstractFactory::addMaterial(GameObject * gameObject)
{
	gameObject->setMaterial(material);
}

void AbstractFactory::addBehaviour(GameObject * gameObject)
{
	gameObject->setBehaviour(behaviour);
}

Mesh * AbstractFactory::getMesh(lua_State * lua)
{
	return Mesh::load(LuaWrapper::GetString(lua, "Mesh"));
}

TextureMaterial * AbstractFactory::getTextureMaterial(lua_State * lua)
{
	return new TextureMaterial(Texture::load(LuaWrapper::GetString(lua, "Texture")));;
}


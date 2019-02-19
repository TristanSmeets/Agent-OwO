#include "TileObject.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include <iostream>

TileObject::TileObject(lua_State* tileLua, const std::string & name, const glm::vec3 & position)
	: GameObject("GameObject: " + name, position)
{
	node = new Node(position,
		LuaWrapper::GetNumber<float>(tileLua, "TileSize"),
		true,
		TILETYPE::GENERIC);
}

TileObject::~TileObject()
{
	GameObject::~GameObject();
	std::cout << "GC running on:TileObject\n";
	delete node;
}

Node * TileObject::GetNode()
{
	return node;
}

void TileObject::SetNodePosition(const glm::vec3& position)
{
	node->SetPosition(position);
}

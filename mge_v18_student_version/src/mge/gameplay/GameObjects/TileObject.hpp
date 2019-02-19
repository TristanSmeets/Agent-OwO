#pragma once

#include "mge/core/GameObject.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"

class Node;

class TileObject : public GameObject
{
public:
	TileObject(lua_State* tileLua, const std::string& name = "TileObject", const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual ~TileObject();
	Node* GetNode();
	void SetNodePosition(const glm::vec3& position);
	void CreateNodeConnections(const std::vector<TileObject*>& tileObjects, int currentTile);

protected:
	Node* node;
};
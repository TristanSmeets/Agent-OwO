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
	static void CreateNodeConnections(const std::vector<TileObject*>& tileObjects);
	static Node* GetNodeAtPosition(const std::vector<TileObject*>& tileObjects, const glm::vec3& position);
	static Node* GetNodeOfType(const std::vector<TileObject*>& tileObjects, const NODETYPE nodeType);

protected:
	Node* node;
	bool hasNeighbouringTile(const DIRECTION& direction, const glm::vec3& other, float tileSize);
};
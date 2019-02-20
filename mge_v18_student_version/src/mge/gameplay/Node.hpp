#pragma once

#include "glm.hpp"
#include <map>
#include <vector>
#include "mge/core/GameObject.hpp"

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum NODETYPE
{
	BOX,
	GENERIC,
	START,
	SWITCH,
	EXIT
};

class Node
{
public:
	Node(const glm::vec3& position = glm::vec3(0,0,0), 
		float size = 1.0f,
		NODETYPE tileType = NODETYPE::GENERIC);

	~Node();
	glm::vec3 GetPosition();
	void SetPosition(const glm::vec3& newPosition);
	float GetSize();
	bool GetIsWalkable();
	void SetNodeType(const NODETYPE& newTileType);
	NODETYPE GetNodeType();
	void AddConnection(DIRECTION direction, Node* node);
	int GetConnectionCount();
	Node* GetConnectionAt(DIRECTION direction);
	bool HasConnection(DIRECTION direction);
	void ResetNodeType();
	void SetCurrentGameObject(GameObject* gameObject);
	void ClearCurrentGameObject();
	GameObject* GetCurrentGameObject();

private:
	glm::vec3 position;
	float tileSize;
	std::map<DIRECTION, Node*> connections;
	NODETYPE tileType;
	NODETYPE startType;
	GameObject* currentGameObject;
};

#pragma once

#include "glm.hpp"
#include <map>
#include <vector>

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum TILETYPE
{
	GENERIC,
	SWITCH,
	EXIT
};

class Node
{
public:
	Node(glm::vec3 position = glm::vec3(0,0,0), 
		float size = 1.0f, 
		bool isWalkable = true, 
		TILETYPE tileType = TILETYPE::GENERIC);

	~Node();
	glm::vec3 GetPosition();
	float GetSize();
	bool GetIsWalkable();
	TILETYPE GetTileType();
	void AddConnection(DIRECTION direction, Node* node);
	int GetConnectionCount();
	Node* GetConnectionAt(DIRECTION direction);
	void CreateConnections(const std::vector<Node*> &nodes, int currentNode);

private:
	glm::vec3 position;
	float tileSize;
	std::map<DIRECTION, Node*> connections;
	bool isWalkable;
	TILETYPE tileType;
};

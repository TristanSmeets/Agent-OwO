#include "Node.hpp"
#include <iostream>

Node::Node(const glm::vec3& position, float size, bool isWalkable, TILETYPE tileType) : 
	position(position), tileSize(size), isWalkable(isWalkable), tileType(tileType)
{
	//std::cout << "Creating Node at: " << position << std::endl;
}

Node::~Node()
{
	std::cout << "GC running on:Node\n";

	for (std::map<DIRECTION, Node*>::iterator itr = connections.begin(), end = connections.end(); itr != end; ++itr)
	{
		itr->second = nullptr;
	}
	connections.clear();
}

glm::vec3 Node::GetPosition()
{
	return position;
}

void Node::SetPosition(const glm::vec3 & newPosition)
{
	std::cout << "Setting NODE to " << newPosition << std::endl;
	position = newPosition;
}

float Node::GetSize()
{
	return tileSize;
}

void Node::SetIsWalkable(bool value)
{
	isWalkable = value;
}

bool Node::GetIsWalkable()
{
	return isWalkable;
}

void Node::SetTileType(const TILETYPE & newTileType)
{
	tileType = newTileType;
}

TILETYPE Node::GetTileType()
{
	return tileType;
}

void Node::AddConnection(DIRECTION direction, Node * node)
{
	connections[direction] = node;
}

int Node::GetConnectionCount()
{
	return connections.size();
}

Node * Node::GetConnectionAt(DIRECTION direction)
{
	return connections[direction];
}

bool Node::HasConnection(DIRECTION direction)
{
	return connections.find(direction) != connections.end();
}


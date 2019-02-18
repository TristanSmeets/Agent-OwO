#include "Node.hpp"
#include <iostream>

Node::Node(glm::vec3 position, float size, bool isWalkable, TILETYPE tileType) : 
	position(position), tileSize(size), isWalkable(isWalkable), tileType(tileType)
{
	std::cout << "Creating Node at: " << position << std::endl;
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

float Node::GetSize()
{
	return tileSize;
}

bool Node::GetIsWalkable()
{
	return isWalkable;
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
	std::map<DIRECTION, Node*>::iterator itr = connections.find(direction);

	if (itr != connections.end())
	{
		return itr->second;
	}
	else
		return nullptr;
}

void Node::CreateConnections(const std::vector<Node*> &nodes, int currentNode)
{
	std::cout << "Creating connections for Node#" << currentNode << std::endl;
	for (int index = 0; index < nodes.size(); ++index)
	{
		if (currentNode != index)
		{
			if (position.x - tileSize < nodes[index]->GetPosition().x + (nodes[index]->GetSize() * 0.5f))
				connections[DIRECTION::LEFT] = nodes[index];
			if (position.x + tileSize > nodes[index]->GetPosition().x - (nodes[index]->GetSize() * 0.5f))
				connections[DIRECTION::RIGHT] = nodes[index];
			if (position.z - tileSize < nodes[index]->GetPosition().z + (nodes[index]->GetSize() * 0.5f))
				connections[DIRECTION::DOWN] = nodes[index];
			if (position.z + tileSize > nodes[index]->GetPosition().z - (nodes[index]->GetSize() * 0.5f))
				connections[DIRECTION::UP] = nodes[index];
		}
	}
}

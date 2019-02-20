#include "Node.hpp"
#include <iostream>

Node::Node(const glm::vec3& position, float size, NODETYPE tileType) : 
	position(position), tileSize(size), tileType(tileType), startType(tileType)
{
	std::cout << "Creating NODE." << std::endl;
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

bool Node::GetIsWalkable()
{
	switch (GetNodeType())
	{
	case NODETYPE::BOX:
		return false;
		break;
	case NODETYPE::EXIT:
		return false;
		break;
	case NODETYPE::GENERIC:
		return true;
		break;
	case NODETYPE::SWITCH:
		return true;
		break;
	default:
		return true;
		break;
	}
}

void Node::SetNodeType(const NODETYPE & newTileType)
{
	tileType = newTileType;
}

NODETYPE Node::GetNodeType()
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

void Node::ResetNodeType()
{
	SetNodeType(startType);
}


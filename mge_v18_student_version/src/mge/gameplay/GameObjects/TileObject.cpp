#include "TileObject.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include <iostream>

TileObject::TileObject(lua_State* tileLua, const std::string & name, const glm::vec3 & position)
	: GameObject(name, position)
{
	node = new Node(position,
		LuaWrapper::GetNumber<float>(tileLua, "TileSize"),
		NODETYPE::GENERIC);
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
	float tileSize = GetNode()->GetSize();
	glm::vec3 correctedPosition = glm::vec3(
		position.x,
		position.y + 0.15f,
		position.z);

	node->SetPosition(correctedPosition);
}

void TileObject::CreateNodeConnections(const std::vector<TileObject*>& tileObjects)
{
	for (unsigned int current = 0; current < tileObjects.size(); ++current)
	{
		TileObject* currentTile = tileObjects[current];
		glm::vec3 position = currentTile->getLocalPosition();
		float tileSize = currentTile->GetNode()->GetSize();
		std::cout << "Creating connections for TileType " << currentTile->GetNode()->GetNodeType() << " Node in TileObject#" << current << std::endl;
		for (int index = 0; index < tileObjects.size(); index++)
		{
			if (index != current)
			{
				glm::vec3 other = tileObjects[index]->getLocalPosition();
				if (currentTile->hasNeighbouringTile(DIRECTION::RIGHT, other, tileSize))
					currentTile->GetNode()->AddConnection(DIRECTION::RIGHT, tileObjects[index]->GetNode());
				else if (currentTile->hasNeighbouringTile(DIRECTION::LEFT, other, tileSize))
					currentTile->GetNode()->AddConnection(DIRECTION::LEFT, tileObjects[index]->GetNode());
				else if (currentTile->hasNeighbouringTile(DIRECTION::DOWN, other, tileSize))
					currentTile->GetNode()->AddConnection(DIRECTION::DOWN, tileObjects[index]->GetNode());
				else if (currentTile->hasNeighbouringTile(DIRECTION::UP, other, tileSize))
					currentTile->GetNode()->AddConnection(DIRECTION::UP, tileObjects[index]->GetNode());
			}
		}
		std::cout << "Amount of Connections: " << currentTile->GetNode()->GetConnectionCount() << std::endl << std::endl;
	}
}

Node * TileObject::GetNodeAtPosition(const std::vector<TileObject*>& tileObjects, const glm::vec3& position)
{
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		glm::vec3 nodePosition = tileObjects[index]->getLocalPosition();
		if (position.x == nodePosition.x &&
			position.y == nodePosition.y &&
			position.z == nodePosition.z)
			return tileObjects[index]->GetNode();
	}
	return nullptr;
}

std::vector<Node*> TileObject::GetNodesOfType(const std::vector<TileObject*>& tileObjects, const NODETYPE nodeType)
{
	std::vector<Node*> nodes;

	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		if (tileObjects[index]->GetNode()->GetNodeType() == nodeType)
			nodes.push_back(tileObjects[index]->GetNode());
	}
	return nodes;
}

void TileObject::ResetNodes(const std::vector<TileObject*>& tileObjects)
{
	for (unsigned int index = 0; index < tileObjects.size(); ++index)
	{
		tileObjects[index]->GetNode()->ResetNode();
	}
}

bool TileObject::hasNeighbouringTile(const DIRECTION & direction, const glm::vec3& other, float tileSize)
{
	glm::vec3 position = getLocalPosition();

	switch (direction)
	{
	case DIRECTION::DOWN:
		return (position.x - tileSize == other.x &&
			position.y == other.y &&
			position.z == other.z);
		break;
	case DIRECTION::LEFT:
		return (position.x == other.x &&
			position.y == other.y &&
			position.z - tileSize == other.z);
		break;
	case DIRECTION::RIGHT:
		return (position.x == other.x &&
			position.y == other.y &&
			position.z + tileSize == other.z);
		break;
	case DIRECTION::UP:
		return (position.x + tileSize == other.x &&
			position.y == other.y &&
			position.z == other.z);
		break;
	}
	return false;
}

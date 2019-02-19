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
	float tileSize = GetNode()->GetSize();
	glm::vec3 correctedPosition = glm::vec3(
		position.x - tileSize * 0.5f,
		position.y,
		position.z + tileSize * 0.5f);

	node->SetPosition(correctedPosition);
}

void TileObject::CreateNodeConnections(const std::vector<TileObject*>& tileObjects, int currentTile)
{
	glm::vec3 position = getLocalPosition();
	float tileSize = GetNode()->GetSize();
	std::cout << "Creating connections for TileType"<< GetNode()->GetTileType() <<" Node in TileObject#" << currentTile << std::endl;
	for (int index = 0; index < tileObjects.size(); index++)
	{
		if (index != currentTile)
		{
			glm::vec3 other = tileObjects[index]->getLocalPosition();
			if (position.x == other.x &&
				position.y == other.y &&
				position.z + tileSize == other.z)
			{
				std::cout << "Creating RIGHT connection with Tile#" << index << std::endl;
				GetNode()->AddConnection(DIRECTION::RIGHT, tileObjects[index]->GetNode());
			}
			else if (position.x == other.x &&
				position.y == other.y &&
				position.z - tileSize == other.z)
			{
				std::cout << "Creating LEFT connection with Tile#" << index << std::endl;
				GetNode()->AddConnection(DIRECTION::LEFT, tileObjects[index]->GetNode());
			}
			else if (position.x - tileSize == other.x &&
				position.y == other.y &&
				position.z == other.z)
			{
				std::cout << "Creating DOWN connection with Tile#" << index << std::endl;
				GetNode()->AddConnection(DIRECTION::DOWN, tileObjects[index]->GetNode());
			}
			else if (position.x + tileSize == other.x &&
				position.y == other.y &&
				position.z == other.z)
			{
				std::cout << "Creating UP connection with Tile#" << index << std::endl;
				GetNode()->AddConnection(DIRECTION::UP, tileObjects[index]->GetNode());
			}
		}
	}
}

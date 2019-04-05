#include "mge/util/LevelEditor/Factories/TileFactory.hpp"

//For printing debug info
#include <iostream>

TileFactory::TileFactory() : AbstractFactory()
{
}

TileFactory::TileFactory(lua_State* config) : AbstractFactory()
{
	std::string tileFile = LuaWrapper::GetString(config, "Tile");
	luaTile = LuaWrapper::InitializeLuaState(tileFile);
	mesh = getMesh(luaTile);
	initializeTextures();
	behaviour = nullptr;
}


TileFactory::~TileFactory()
{
	AbstractFactory::~AbstractFactory();
	mesh = nullptr;
	for (unsigned int index = 0; index < textureMaterials.size(); ++index)
	{
		delete textureMaterials[index];
	}
	textureMaterials.clear();

	LuaWrapper::CloseLuaState(luaTile);
}

GameObject* TileFactory::CreateGameObject(const std::string& name)
{
	TileObject* newTileObject = new TileObject(luaTile, name);
	addMesh(newTileObject);
	
	int randomValue = rand() % textureMaterials.size();
	newTileObject->setMaterial(textureMaterials[randomValue]);
	return newTileObject;
}

void TileFactory::SetRandomSeed(int seed)
{
	std::srand(seed);
}

void TileFactory::initializeTextures()
{
	lua_getglobal(luaTile, "Textures");

	lua_pushnil(luaTile);

	while (lua_next(luaTile, -2) != 0)
	{
		if (lua_isstring(luaTile, -1))
		{
			std::string currentPath = lua_tostring(luaTile, -1);
			TextureMaterial* currentTexture = new TextureMaterial(Texture::load(currentPath));
			textureMaterials.push_back(currentTexture);
		}
		lua_pop(luaTile, 1);
	}
	lua_pop(luaTile, 1);
}

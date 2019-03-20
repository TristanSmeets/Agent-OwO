#pragma once

#include "mge/util/LevelEditor/Factories/AbstractFactory.hpp"
#include "mge/gameplay/GameObjects/TileObject.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include <stdlib.h>
#include <vector>

class TileFactory :
	public AbstractFactory
{
public:
	TileFactory();
	TileFactory(lua_State* config);
	virtual ~TileFactory();
	GameObject* CreateGameObject(const std::string& name);
	void SetRandomSeed(int seed);
private:
	lua_State* luaTile;
	std::vector<TextureMaterial*> textureMaterials;
	void initializeTextures();

};
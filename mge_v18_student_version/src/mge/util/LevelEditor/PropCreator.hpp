#pragma once

#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/core/Camera.hpp"
#include <vector>

class PropCreator
{
public:
	PropCreator(World* world);
	~PropCreator();
	void LoadProps();
	void CreateBGProp(int level);
	void RemoveBGProp();

private:
	lua_State* luaLevelInfo;
	World* world;
	GameObject* backgroundObject;
	GameObject* skyboxPlane;
	Mesh* skyboxMesh;
	std::vector<Mesh*> backgroundMeshes;
	std::vector<TextureMaterial*> backgroundMaterials;
	std::vector<TextureMaterial*> skyboxMaterials;
	void loadMeshes();
	void loadMaterials();
};
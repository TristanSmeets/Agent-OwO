#include "PropCreator.hpp"

PropCreator::PropCreator(World* world) : world(world)
{
	std::cout << "Creating PropCreator.\n";
	luaLevelInfo = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_Info.lua");
}

PropCreator::~PropCreator()
{
	std::cout << "GC running on:PropCreator.\n";
	world = nullptr;
	backgroundObject = nullptr;

	for (unsigned int index = 0; index < backgroundMeshes.size(); ++index)
	{
		backgroundMeshes[index] = nullptr;
	}
	backgroundMeshes.clear();

	for (unsigned int index = 0; index < backgroundMaterials.size(); ++index)
	{
		delete backgroundMaterials[index];
		backgroundMaterials[index] = nullptr;
	}
	backgroundMaterials.clear();

	LuaWrapper::CloseLuaState(luaLevelInfo);
}

void PropCreator::LoadProps()
{
	loadMaterials();
	loadMeshes();
}

void PropCreator::CreateBGProp(int level)
{
	backgroundObject = new GameObject("BACKGROUNDPROP");
	backgroundObject->setMesh(backgroundMeshes[level]);
	backgroundObject->setMaterial(backgroundMaterials[level]);
	world->add(backgroundObject);
}

void PropCreator::RemoveBGProp()
{
	world->remove(backgroundObject);
	backgroundObject->setMaterial(nullptr);
	backgroundObject->setMesh(nullptr);
	delete backgroundObject;
}

void PropCreator::loadMeshes()
{
	unsigned int tableSize = LuaWrapper::GetNumber<int>(luaLevelInfo, "BGMeshSize");
	std::cout << "Mesh Size: " << tableSize << std::endl;

	lua_getglobal(luaLevelInfo, "BackgroundMesh");

	for (unsigned int index = 0; index < tableSize; ++index)
	{
		std::string current = "Level_" + std::to_string(index + 1);
		std::string meshPath = LuaWrapper::GetTableString(luaLevelInfo, current);
		backgroundMeshes.push_back(Mesh::load(meshPath));
	}
	lua_pop(luaLevelInfo, 1);
	std::cout << "BackgroundMeshes size: " << backgroundMeshes.size() << std::endl;
}

void PropCreator::loadMaterials()
{
	unsigned int tableSize = LuaWrapper::GetNumber<int>(luaLevelInfo, "BGTextureSize");
	std::cout << "Texture Size: " << tableSize << std::endl;

	lua_getglobal(luaLevelInfo, "BackgroundTexture");

	for (unsigned int index = 0; index < tableSize; ++index)
	{
		std::string current = "Level_" + std::to_string(index + 1);
		std::string texturePath = LuaWrapper::GetTableString(luaLevelInfo, current);
		std::cout << "Creating Texture#" << (index + 1) << std::endl;
		backgroundMaterials.push_back(new TextureMaterial(Texture::load(texturePath)));
	}
	lua_pop(luaLevelInfo, 1);
	std::cout << "BackgroundMaterials size: " << backgroundMaterials.size() << std::endl;
}


#include "PropCreator.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

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
	backgroundObject->setMesh(backgroundMeshes[level - 1]);
	backgroundObject->setMaterial(backgroundMaterials[level - 1]);
	world->add(backgroundObject);

	skyboxPlane = new GameObject("SKYBOX");
	glm::quat rotation; 
	glm::vec3 position; 
	lua_State* luaLevel = LuaWrapper::InitializeLuaState("LuaGameScripts/Level/Level_" + std::to_string(level) + ".lua");

	lua_getglobal(luaLevel,"GameObjects");

	lua_pushnil(luaLevel);
	while (lua_next(luaLevel, -2) != 0)
	{
		std::string typeString = LuaWrapper::GetTableString(luaLevel, "Type");

		if (typeString == "CAMERA")
		{
			rotation = LuaWrapper::GetTableQuat(luaLevel, "Rotation");
			position = LuaWrapper::GetTableVec3(luaLevel, "Position");
		}
		lua_pop(luaLevel, 1);
	}
	lua_pop(luaLevel, 1);
	
	glm::mat4 rotationMatrix = glm::toMat4(rotation);
	glm::mat4 translation = glm::translate(glm::vec3(position.x, position.y, position.z));
	skyboxPlane->setTransform(translation * rotationMatrix);
	skyboxPlane->rotate(glm::radians(-90.0f), glm::vec3(0, 1, 0));
	skyboxPlane->translate(glm::vec3(80.0, 0.0f, 0.0f));
	skyboxPlane->setMesh(skyboxMesh);
	skyboxPlane->setMaterial(skyboxMaterials[level - 1]);
	world->add(skyboxPlane);
}

void PropCreator::RemoveBGProp()
{
	world->remove(backgroundObject);
	backgroundObject->setMaterial(nullptr);
	backgroundObject->setMesh(nullptr);
	delete backgroundObject;
	world->remove(skyboxPlane);
	skyboxPlane->setMaterial(nullptr);
	skyboxPlane->setMesh(nullptr);
	delete skyboxPlane;
}

void PropCreator::loadMeshes()
{
	unsigned int levels = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");

	lua_getglobal(luaLevelInfo, "BackgroundMesh");

	for (unsigned int index = 0; index < levels; ++index)
	{
		std::string current = "Level_" + std::to_string(index + 1);
		std::string meshPath = LuaWrapper::GetTableString(luaLevelInfo, current);
		backgroundMeshes.push_back(Mesh::load(meshPath));
	}
	lua_pop(luaLevelInfo, 1);

	std::string skyboxPath = LuaWrapper::GetString(luaLevelInfo, "SkyBoxMesh");
	skyboxMesh = Mesh::load(skyboxPath);
}

void PropCreator::loadMaterials()
{
	unsigned int tableSize = LuaWrapper::GetNumber<int>(luaLevelInfo, "Levels");

	lua_getglobal(luaLevelInfo, "BackgroundTexture");

	for (unsigned int index = 0; index < tableSize; ++index)
	{
		std::string current = "Level_" + std::to_string(index + 1);
		std::string texturePath = LuaWrapper::GetTableString(luaLevelInfo, current);
		backgroundMaterials.push_back(new TextureMaterial(Texture::load(texturePath)));
	}
	lua_pop(luaLevelInfo, 1);

	lua_getglobal(luaLevelInfo, "SkyBoxTexture");
	for (unsigned int index = 0; index < tableSize; ++index)
	{
		std::string current = "Level_" + std::to_string(index + 1);
		std::string texturePath = LuaWrapper::GetTableString(luaLevelInfo, current);
		skyboxMaterials.push_back(new TextureMaterial(Texture::load(texturePath)));
	}
	lua_pop(luaLevelInfo, 1);
}


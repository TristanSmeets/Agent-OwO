#pragma once
#include "mge/util/LevelEditor/Factories/BoxFactory.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/util/LevelEditor/Factories/ExitFactory.hpp"
#include "mge/util/LevelEditor/Factories/PlayerFactory.hpp"
#include "mge/util/LevelEditor/Factories/StartFactory.hpp"
#include "mge/util/LevelEditor/Factories/SwitchFactory.hpp"
#include "mge/util/LevelEditor/Factories/TileFactory.hpp"
#include "mge/core/World.hpp"
#include <vector>
#include "glm.hpp"
#include <glm/gtx/quaternion.hpp>

class ObjectCreator
{
public:
	ObjectCreator(lua_State* config, World* world, Camera* camera);
	~ObjectCreator();
	void CreateGameObject(const std::string& objectType, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
	void ConfigureBehaviourStartNodes();
	void ResetMovableObjects();
	void resetExit();
	void SetRandomSeed(int seed);

	std::vector<TileObject*>& GetTileObjects();
	std::vector<GameObject*>& GetBoxObjects();
	std::vector<GameObject*>& GetSwitchObjects();
	GameObject* GetPlayer();
	GameObject* GetExit();

private:
	void configureBoxes();
	void configurePlayer();
	void resetBoxes();

	lua_State* config;
	World* world;
	BoxFactory* boxFactory;
	CameraFactory* cameraFactory;
	ExitFactory* exitFactory;
	PlayerFactory* playerFactory;
	StartFactory* startFactory;
	SwitchFactory* switchFactory;
	TileFactory* tileFactory;
	GameObject* playerObject;
	GameObject* exitObject;
	GameObject* cameraObject = nullptr;
	std::vector<TileObject*> tileObjects;
	std::vector<GameObject*> boxObjects;
	std::vector<GameObject*> switchObjects;
	std::vector<Node*> boxStartingNodes;
	
	
	void addToTileObjectsandSetNode(GameObject * newGameObject, const glm::vec3 & position);
};
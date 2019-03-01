#include "mge/scenes/GameScene.hpp"
#include <iostream>

GameScene::GameScene() : AbstractGame(), config(LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua"))
{
}

GameScene::~GameScene()
{
	std::cout << "GC running on:GameScene\n";
	delete level;
	delete eventQueueBehaviour;

	std::cout << "Cleaning up Buttons.\n";
	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			ButtonManager::RemoveButton(current);
			delete current;
		}
	}
	backgroundMesh = nullptr;
	delete backgroundTexture;
	//if(mainMenu != nullptr) delete mainMenu;
}

void GameScene::initialize()
{
	AbstractGame::initialize();
}

void GameScene::OnNotify(const GeneralEvent & info)
{
	if (info.startGame)
	{
		delete mainMenu;
		level->CreateLevel(1);
	}
}

void GameScene::_initializeScene()
{
	GameObject* eventQueue = new GameObject("EventQueue");
	eventQueueBehaviour = new EventQueueBehaviour();
	eventQueue->setBehaviour(eventQueueBehaviour);
	_world->add(eventQueue);

	EventQueue::AddObserver(this);

	lua_State* config = LuaWrapper::InitializeLuaState("LuaGameScripts\\config.lua");

	Camera* camera = dynamic_cast<Camera*>(CameraFactory(config).CreateGameObject("Camera"));
	_world->add(camera);
	_world->setMainCamera(camera);

	//std::cout << "Creating MainMenu.\n";
	//mainMenu = new MainMenu(_world, _window);

	GameObject* background = new GameObject("BACKGROUND", glm::vec3(-2,0,4));
	backgroundMesh = Mesh::load(config::MGE_MODEL_PATH + "Level_2_BG.obj");
	backgroundTexture = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Level_2_BG.png"));
	background->setMesh(backgroundMesh);
	background->setMaterial(backgroundTexture);
	_world->add(background);


	std::cout << "Creating the Level\n";
	level = new Level(_world, camera);
	level->CreateLevel(2);
}

void GameScene::_render()
{
	AbstractGame::_render();

	if (ButtonManager::GetAmountOfButtons() > 0)
	{
		for (unsigned int index = 0; index < ButtonManager::GetAmountOfButtons(); ++index)
		{
			Button* current = ButtonManager::GetButton(index);
			_window->pushGLStates();
			_window->draw(*current->GetSprite());
			_window->popGLStates();
		}
	}
}


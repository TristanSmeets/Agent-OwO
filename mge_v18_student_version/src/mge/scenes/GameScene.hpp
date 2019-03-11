#pragma once

#include "mge/core/AbstractGame.hpp"
#include "mge/util/LevelEditor/Level.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/behaviours/QueueBehaviour.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include "mge/User Interface/MainMenu.hpp"
#include "mge/User Interface/HUD.hpp"
#include "mge/util/LevelEditor/PropCreator.hpp"
#include "mge/User Interface/DeathScreen.hpp"
#include "mge/User Interface/PauseScreen.hpp"
#include "mge/User Interface/CreditsScreen.hpp"
#include "mge/User Interface/ControleScreen.hpp"
#include "mge/Audio/AudioBank.hpp"
#include "mge/Audio/AudioManager.hpp"
#include "mge/Audio/AudioLocator.hpp"

class GameScene : public AbstractGame, public Observer<GeneralEvent>
{
public:
	GameScene();
	~GameScene();
	void initialize();
	void OnNotify(const GeneralEvent& info);

protected:
	void _initializeScene();
	void _render();

private:
	AudioManager* audioManager;
	Level* level = nullptr;
	HUD* hud = nullptr;
	MainMenu* mainMenu = nullptr;
	DeathScreen* deathScreen = nullptr;
	PauseScreen* pauseScreen = nullptr;
	CreditsScreen* creditsScreen = nullptr;
	ControleScreen* controleScreen = nullptr;
	lua_State* config;
	QueueBehaviour* eventQueueBehaviour;
	Camera* camera;
	PropCreator* propCreator;

	int levelNumber = 1;
	int amountOfLevels = 0;
};
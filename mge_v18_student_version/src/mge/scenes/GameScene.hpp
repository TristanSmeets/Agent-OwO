#pragma once

#include "mge/core/AbstractGame.hpp"
#include "mge/util/LevelEditor/Level.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/behaviours/EventQueueBehaviour.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include "mge/User Interface/MainMenu.hpp"
#include "mge/User Interface/HUD.hpp"

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
	Level* level;
	lua_State* config;
	HUD* hud = nullptr;
	EventQueueBehaviour* eventQueueBehaviour;
	MainMenu* mainMenu;
	int levelNumber = 1;
};
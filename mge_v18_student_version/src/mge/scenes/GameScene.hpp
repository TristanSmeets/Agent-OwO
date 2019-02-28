#pragma once

#include "mge/core/AbstractGame.hpp"
#include "mge/util/LevelEditor/Level.hpp"
#include "mge/util/LuaScripting/LuaWrapper.hpp"
#include "mge/behaviours/EventQueueBehaviour.hpp"
#include "mge/gameplay/ButtonManager.hpp"
#include "mge/util/LevelEditor/Factories/CameraFactory.hpp"
#include "mge/core/Camera.hpp"
#include "mge/User Interface/MainMenu.hpp"

class GameScene : public AbstractGame
{
public:
	GameScene();
	~GameScene();
	void initialize();

protected:
	void _initializeScene();
	void _render();

private:
	Level* level;
	lua_State* config;
	EventQueueBehaviour* eventQueueBehaviour;
	MainMenu* mainMenu;
};
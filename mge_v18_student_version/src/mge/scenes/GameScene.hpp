#pragma once

#include "mge/core/AbstractGame.hpp"
#include "mge/util/LevelEditor/Level.hpp"

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
};
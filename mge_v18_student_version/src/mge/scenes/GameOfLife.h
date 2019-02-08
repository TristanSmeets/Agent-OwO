#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "mge/core/AbstractGame.hpp"
#include "mge/util/LuaScripting/DisplayGrid.h"
#include "mge/util/DebugHud.hpp"
#include <lua.hpp>

class GameOfLife : public AbstractGame
{
public:
	GameOfLife();
	virtual ~GameOfLife();
	virtual void initialize();

protected:
	virtual void _initializeScene();
	virtual void _render();

private:
	GameOfLife(const GameOfLife&);
	GameOfLife& operator=(const GameOfLife&);
	DisplayGrid* displayGrid;
	lua_State* main;
	
	DebugHud* hud;
	void updateHud();

};

#endif
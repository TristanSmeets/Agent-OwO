#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "mge/core/AbstractGame.hpp"

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
	sf::RectangleShape rectangle;
};

#endif
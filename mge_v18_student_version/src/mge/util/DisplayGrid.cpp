#include <cassert>
#include <cmath>
#include "DisplayGrid.h"
#include "LuaWrapper.hpp"
#include <GL/glew.h>
#include <iostream>
#include "mge/util/DrawRectangle.hpp"
#include <vector>

std::vector<DrawRectangle*> DisplayGrid::rectangles;

DisplayGrid::DisplayGrid(sf::RenderWindow * renderWindow) : window(renderWindow)
{
	assert(window != NULL);

	std::cout << "Setting up DisplayGrid" << std::endl;
	setupGrid();
	initializeLuaDrawRectangle();
}

DisplayGrid::~DisplayGrid()
{
	//Clearing the 2D Vector
	for (unsigned Index = 0; Index < rectangle2DVector.size(); Index++)
	{
		rectangle2DVector[Index].clear();
	}
	rectangle2DVector.clear();
	
	rectangles.clear();
}

void DisplayGrid::Draw()
{
	glActiveTexture(GL_TEXTURE0);

	window->pushGLStates();
	
	for (unsigned Row = 0; Row < rectangle2DVector.size(); Row++)
	{
		for (unsigned Column = 0; Column < rectangle2DVector[Row].size(); Column++)
		{
			window->draw(rectangle2DVector[Row][Column]);
		}
	}
	window->popGLStates();
}

void DisplayGrid::SetRectangleColour(const sf::Color &colour, const sf::Vector2i &position)
{
	rectangle2DVector[position.y][position.x].setFillColor(colour);
}

void DisplayGrid::AddDrawRectangle(DrawRectangle* rectangle)
{
	rectangles.push_back(rectangle);
}


void DisplayGrid::setupGrid()
{
	lua_State *config = LuaWrapper::InitializeLuaState("config.lua");
	int ScreenWidth = LuaWrapper::GetNumber<int>(config, "ScreenWidth");
	int ScreenHeight = LuaWrapper::GetNumber<int>(config, "ScreenHeight");
	squareSize = LuaWrapper::GetNumber<float>(config, "SquareSize");
	LuaWrapper::CloseLuaState(config);

	columns = floor(ScreenWidth / squareSize);
	rows = floor(ScreenHeight / squareSize);
	rectangle2DVector.resize(rows, std::vector<sf::RectangleShape>(columns));
	
	for (int Row = 0; Row < rectangle2DVector.size(); Row++)
	{
		for (int Column = 0; Column < rectangle2DVector[Row].size(); Column++)
		{
			int x = Column * squareSize;
			int y = Row * squareSize;
			rectangle2DVector[Row][Column].setPosition(sf::Vector2f(x, y));
			rectangle2DVector[Row][Column].setSize(sf::Vector2f(squareSize - 1, squareSize - 1));
			rectangle2DVector[Row][Column].setFillColor(sf::Color::Magenta);
		}
	}
}

void DisplayGrid::initializeLuaDrawRectangle()
{
	DrawRectangle::InitializeLua();
}

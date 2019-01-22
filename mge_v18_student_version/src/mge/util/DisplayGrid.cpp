#include <cassert>
#include <cmath>
#include "DisplayGrid.h"
#include "LuaWrapper.hpp"
#include <GL/glew.h>
#include <iostream>
#include <vector>

std::vector<DrawRectangle*> DisplayGrid::rectangles;

DisplayGrid::DisplayGrid(sf::RenderWindow * renderWindow) : window(renderWindow)
{
	assert(window != NULL);

	std::cout << "Setting up DisplayGrid" << std::endl;
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
	
	for (unsigned index = 0; index < rectangles.size(); index++)
	{
		window->draw(rectangles[index]->GetRectangleShape());
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

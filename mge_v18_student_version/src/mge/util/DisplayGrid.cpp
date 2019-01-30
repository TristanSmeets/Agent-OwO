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
	std::cout << "GC running on:DiplayGrid" << std::endl;
	/*
	for (int index = 0; index < rectangles.size(); index++)
	{
		if (!rectangles[index]) continue;

		delete rectangles[index];
	}*/
	rectangles.clear();
	std::cout << "Rectangles Capacity: " << rectangles.capacity() << std::endl;
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

void DisplayGrid::AddDrawRectangle(DrawRectangle* rectangle)
{
	rectangles.push_back(rectangle);
}

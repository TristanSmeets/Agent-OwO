#include <cassert>
#include <cmath>
#include "DisplayGrid.h"
#include "LuaWrapper.hpp"
#include <GL/glew.h>
#include <iostream>
#include <vector>

std::vector<RectangleShapeWrapper*> DisplayGrid::rectangles;

DisplayGrid::DisplayGrid(sf::RenderWindow * renderWindow) : window(renderWindow)
{
	assert(window != NULL);

	std::cout << "Setting up DisplayGrid" << std::endl;
}

DisplayGrid::~DisplayGrid()
{
	std::cout << "GC running on:DiplayGrid" << std::endl;
	window = nullptr;

	std::cout << "Before Rectangles Capacity: " << rectangles.capacity() << std::endl;
	rectangles.clear();
	rectangles.shrink_to_fit();
	std::cout << "After Rectangles Capacity: " << rectangles.capacity() << std::endl;
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

void DisplayGrid::AddRectangleShape(RectangleShapeWrapper* rectangle)
{
	rectangles.push_back(rectangle);
}

#include <cassert>

#include "DisplayGrid.h"


DisplayGrid::DisplayGrid(sf::RenderWindow * renderWindow) : window(renderWindow)
{
	assert(window != NULL);

}

DisplayGrid::~DisplayGrid()
{
}

sf::RectangleShape ** DisplayGrid::create2DRectangleGrid(unsigned columns, unsigned rows)
{
	sf::RectangleShape** RectangleArray = 0;
	RectangleArray = new sf::RectangleShape*[rows];

	for (int Row = 0; Row < rows; Row++)
	{
		RectangleArray[Row] = new sf::RectangleShape[columns];

		for (int Column = 0; columns < columns; Column++)
		{
			RectangleArray[Row][Column] = sf::RectangleShape();
		}
	}

	return RectangleArray;
}

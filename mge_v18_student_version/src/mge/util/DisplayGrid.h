#ifndef DISPLAYGRID_H
#define DISPLAYGRID_H

#include <SFML/Graphics.hpp>
#include <vector>

/*Class that creates and renders a grid of rectangles through SFML*/
class DisplayGrid
{
public:
	DisplayGrid(sf::RenderWindow* renderWindow);
	virtual ~DisplayGrid();
	void Draw();
	void SetRectangleColour(const sf::Color &colour, const sf::Vector2i &position);

private:
	sf::RenderWindow * window;
	std::vector<std::vector<sf::RectangleShape>> rectangle2DVector;
	sf::RectangleShape rectangle;
	int columns;
	int rows;
	float squareSize;
	void setupGrid();
};

#endif // !DISPLAYGRID_H

#ifndef DISPLAYGRID_H
#define DISPLAYGRID_H

#include <SFML/Graphics.hpp>

/*Class that creates and renders a grid of rectangles through SFML*/
class DisplayGrid
{
public:
	DisplayGrid(sf::RenderWindow* renderWindow);
	virtual ~DisplayGrid();
	void Draw();
	void SetRectangleColour(const sf::Color &colour, const sf::Vector2f position);

private:
	sf::RenderWindow * window;

	sf::RectangleShape** create2DRectangleGrid(unsigned width, unsigned height );

	sf::RectangleShape** rectangle2DArray;

};

#endif // !DISPLAYGRID_H

#ifndef DISPLAYGRID_H
#define DISPLAYGRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "mge/util/DrawRectangle.hpp"

/*Class that creates and renders a grid of rectangles through SFML*/
class DisplayGrid
{
public:
	DisplayGrid(sf::RenderWindow* renderWindow);
	virtual ~DisplayGrid();
	void Draw();
	static void AddDrawRectangle(DrawRectangle* rectangle);

private:
	sf::RenderWindow * window;
	static std::vector<DrawRectangle*> rectangles;
};

#endif // !DISPLAYGRID_H

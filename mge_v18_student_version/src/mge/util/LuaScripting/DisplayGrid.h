#ifndef DISPLAYGRID_H
#define DISPLAYGRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "mge/util/LuaScripting/RectangleShapeWrapper.hpp"

/*Class that creates and renders a grid of rectangles through SFML*/
class DisplayGrid
{
public:
	DisplayGrid(sf::RenderWindow* renderWindow);
	virtual ~DisplayGrid();
	void Draw();
	static void AddRectangleShape(RectangleShapeWrapper* rectangle);

private:
	sf::RenderWindow * window;
	static std::vector<RectangleShapeWrapper*> rectangles;
};

#endif // !DISPLAYGRID_H

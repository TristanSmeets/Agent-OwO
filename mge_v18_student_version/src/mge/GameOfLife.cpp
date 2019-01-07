#include <string>
#include "glm.hpp"
//Core
#include "mge/core/Renderer.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
//Materials
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "GameOfLife.h"

GameOfLife::GameOfLife():AbstractGame()
{
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::initialize()
{
	AbstractGame::initialize();
}

void GameOfLife::_initializeScene()
{
	std::cout << "Creating Camera" << std::endl;
	Camera* camera = new Camera("camera", glm::vec3(0, 0, 15));
	_world->add(camera);
	_world->setMainCamera(camera);

	std::cout << "Creating a rectangle" << std::endl;
	rectangle = sf::RectangleShape(sf::Vector2f(120, 50));
	rectangle.setFillColor(sf::Color(255, 0, 0, 255));
	rectangle.setPosition(sf::Vector2f(50, 20));
}

void GameOfLife::_render()
{
	AbstractGame::_render();
	_window->draw(rectangle);
}

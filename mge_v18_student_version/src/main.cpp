#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/scenes/MGEDemo.hpp"
#include "mge/scenes/TristanScene.h"
#include "mge/scenes/BrokenOBJ.hpp"
#include "mge/scenes/GameOfLife.h"
#include "mge/scenes/TerrainScene.hpp"
#include "mge/scenes/DesignerScene.hpp"
#include <lua.hpp>
/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */

int main()
{
    std::cout << "Starting Game" << std::endl;

    //AbstractGame* game = new MGEDemo();
	//AbstractGame* game = new TristanScene();			//Assignment 1 + 3
	//AbstractGame* game = new BrokenOBJ();				//Assignment 2
	//AbstractGame* game = new TerrainScene();			//Assignment 4
	//AbstractGame* game = new GameOfLife();				//LuaGame
	AbstractGame* game = new DesignerScene();
	game->initialize();
    game->run();

	delete game;

    return 0;
}




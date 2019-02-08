#include "Level.hpp"

Level::Level(World * world) : world(world)
{
}

void Level::SetFactory(AbstractFactory * factory)
{
	this->factory = factory
}

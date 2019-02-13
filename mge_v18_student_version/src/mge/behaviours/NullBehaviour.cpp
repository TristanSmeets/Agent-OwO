#include "NullBehaviour.hpp"
#include <iostream>

NullBehaviour::NullBehaviour()
{
}

NullBehaviour::~NullBehaviour()
{
	std::cout << "GC running on:NullBehaviour\n";
}

void NullBehaviour::update(float step)
{
}
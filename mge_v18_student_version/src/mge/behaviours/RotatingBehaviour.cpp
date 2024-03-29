#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour():AbstractBehaviour()
{
	//ctor
}

RotatingBehaviour::~RotatingBehaviour()
{
	//dtor
}

void RotatingBehaviour::update(float pStep)
{
    //rotates 45� per second
	_owner->rotate(pStep * glm::radians(45.0f), glm::vec3( 0, 1.0f, 0 ) );
}

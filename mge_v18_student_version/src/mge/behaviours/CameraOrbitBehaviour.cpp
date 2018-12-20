#include "CameraOrbitBehaviour.hpp"

CameraOrbitBehaviour::CameraOrbitBehaviour(float distance, float tilt, float rotationSpeed, GameObject* target) :
	AbstractBehaviour(), distance(distance), tilt(tilt), rotationSpeed(rotationSpeed), target(target)
{
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
}

void CameraOrbitBehaviour::update(float step)
{
}

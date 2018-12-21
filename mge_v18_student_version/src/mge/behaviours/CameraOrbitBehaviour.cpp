#include "CameraOrbitBehaviour.hpp"

CameraOrbitBehaviour::CameraOrbitBehaviour(const glm::vec3& distance, float tiltInDegrees, float rotationSpeed, GameObject* target) :
	AbstractBehaviour(), rotationSpeed(rotationSpeed), target(target)
{
	//Set the owner's transform to the correct distance from the target
	_owner->setTransform(glm::translate(distance));

	//Set the tilt
	glm::rotate(_owner->getTransform(), glm::radians(tiltInDegrees), glm::vec3(1.0f, 0, 0));
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
}

void CameraOrbitBehaviour::update(float step)
{
}

/*Rotate around a target:
		- Subtract the target's tranform from the camera's tranform
		- Rotate a certain amount of radians around a specified axis
		- Add the target's transform back to the camera's transform*/
glm::mat4 CameraOrbitBehaviour::rotateAroundTarget(float rotationsRadians, const glm::vec3& rotationAxis) const
{
	glm::mat4& tempCameraMat = _owner->getTransform() - target->getTransform();
	glm::rotate(tempCameraMat, rotationsRadians, rotationAxis);
	return tempCameraMat + target->getTransform();
}

void CameraOrbitBehaviour::mouseInput()
{}

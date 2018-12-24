#include "CameraOrbitBehaviour.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

CameraOrbitBehaviour::CameraOrbitBehaviour(float distance, float maxTilt, float rotationSpeed, GameObject* target, sf::Window* window) :
	AbstractBehaviour(), maxTilt(maxTilt), rotationSpeed(rotationSpeed), target(target), oldMousePos(sf::Mouse::getPosition(*window)), window(window)
{
	//Target position
	targetPosition = (*target).getWorldPosition();
	//Camera position
	cameraPosition = glm::vec3(targetPosition.x, targetPosition.y, targetPosition.z + distance);
	std::cout << "oldMousePos: " << oldMousePos.x << "," << oldMousePos.y << std::endl;
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
	target = nullptr;
	window = nullptr;
}

void CameraOrbitBehaviour::update(float step)
{
	mouseInput();
}

/*Rotate around a target:
		- Subtract the target's position from the camera's position
		- Rotate a certain amount of radians around a specified axis
		- Add the target's position back to the camera's position*/
glm::vec3 CameraOrbitBehaviour::rotateAroundTarget(float rotationsRadians, const glm::vec3& rotationAxis) const
{
	glm::vec3& tempCameraPosition = cameraPosition - targetPosition;
	glm::rotate(tempCameraPosition, rotationsRadians, rotationAxis);
	return glm::rotate(tempCameraPosition, rotationsRadians, rotationAxis) + targetPosition;
}

void CameraOrbitBehaviour::mouseInput()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2u screenSize = window->getSize();

	//Horizontal movement
	float halfScreenWidth = (float)screenSize.x / 2;
	float mouseDistance = mousePosition.x - halfScreenWidth;
	float turnSpeed = rotationSpeed * (mouseDistance / halfScreenWidth);
	cameraPosition = rotateAroundTarget(glm::radians(turnSpeed), glm::vec3(0, 1, 0));

	//Vertical movement (not working correctly yet when combined with horizontal)
	//float halfScreenHeight = screenSize.y / 2;
	//float mouseYDistance = mousePosition.y - halfScreenHeight;
	//float yTurnSpeed = rotationSpeed * (mouseYDistance / halfScreenHeight);
	//tiltInDegrees += yTurnSpeed;

	//if (tiltInDegrees <= maxTilt && tiltInDegrees >= -maxTilt)
	//{
	//	cameraPosition = rotateAroundTarget(glm::radians(yTurnSpeed), glm::vec3(1, 0, 0));
	//}

	//This correctly targets the camera on the target object.
	_owner->setTransform(glm::inverse(glm::lookAt(cameraPosition, targetPosition, glm::vec3(0, 1, 0))));
}

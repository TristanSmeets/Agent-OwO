#include "CameraOrbitBehaviour.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

CameraOrbitBehaviour::CameraOrbitBehaviour(float distance, float maxTilt, float rotationSpeed, GameObject* target, sf::Window* window) :
	AbstractBehaviour(), distance(distance), maxTilt(maxTilt), rotationSpeed(rotationSpeed), target(target), oldMousePos(sf::Mouse::getPosition(*window)), window(window)
{
}

CameraOrbitBehaviour::~CameraOrbitBehaviour()
{
	std::cout << "GC running on:CameraOrbitBehaviour" << std::endl;
	target = nullptr;
	window = nullptr;
}

void CameraOrbitBehaviour::update(float step)
{
	mouseInput(step);
}

float CameraOrbitBehaviour::clamp(float value, float min, float max)
{
	return std::min(max, std::max(value, min));
}

void CameraOrbitBehaviour::mouseInput(float step)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2u screenSize = window->getSize();

	//Horizontal movement
	float halfScreenWidth = screenSize.x / 2;
	float mouseDistance = mousePosition.x - halfScreenWidth;
	float turnSpeed = rotationSpeed * (mouseDistance / halfScreenWidth);
	horizontalAngle += turnSpeed;

	//Create horizontal rotation matrix
	glm::mat4 horizontalRotation = glm::rotate(glm::radians(horizontalAngle), glm::vec3(0, 1, 0));

	//Vertical movement (not working correctly yet when combined with horizontal)
	float halfScreenHeight = screenSize.y / 2;
	float mouseYDistance = mousePosition.y - halfScreenHeight;
	float yTurnSpeed = rotationSpeed * (mouseYDistance / halfScreenHeight);
	verticalAngle += yTurnSpeed;
	verticalAngle = clamp(verticalAngle, -maxTilt, maxTilt);

	//Create vertical rotation matrix
	glm::mat4 verticalRotation = glm::rotate(glm::radians(verticalAngle), glm::vec3(1, 0, 0));

	glm::mat4 targetMatrix = target->getWorldTransform();
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, distance));
	glm::mat4 rotationMatrix = horizontalRotation * verticalRotation;

	//This correctly targets the camera on the target object.
	_owner->setTransform(targetMatrix * rotationMatrix * translationMatrix);
}

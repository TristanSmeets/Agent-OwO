#ifndef CAMERAORBITBEHAVIOUR_HPP
#define CAMERAORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Window.hpp>

class CameraOrbitBehaviour : public AbstractBehaviour
{
public:
	CameraOrbitBehaviour(float distance, float maxTilt, float rotationSpeed, GameObject* target, sf::Window* window);
	virtual ~CameraOrbitBehaviour();
	virtual void update(float step);

private:
	float rotationSpeed;
	GameObject* target;
	sf::Window* window;
	glm::vec3 cameraPosition;
	glm::vec3 targetPosition;
	glm::vec3 cameraForward;
	glm::vec3 cameraSide;
	glm::vec3 cameraUp;
	float tiltInDegrees = 0.0f;
	float maxTilt;
	sf::Vector2i oldMousePos;
	glm::vec3 rotateAroundTarget(float rotationsRadians, const glm::vec3& rotationAxis ) const;
	void mouseInput();
};

#endif
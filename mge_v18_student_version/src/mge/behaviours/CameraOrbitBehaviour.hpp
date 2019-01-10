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
	float distance = 0;
	float rotationSpeed = 0;
	float verticalAngle = 0;
	float horizontalAngle = 0;
	float maxTilt;
	GameObject* target;
	sf::Window* window;
	sf::Vector2i oldMousePos;
	float test;
	void mouseInput(float step);
	float clamp(const float value, const float min, const float max);
};

#endif

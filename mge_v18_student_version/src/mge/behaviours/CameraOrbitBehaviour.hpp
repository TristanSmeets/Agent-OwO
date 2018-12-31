#ifndef CAMERAORBITBEHAVIOUR_HPP
#define CAMERAORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"

class CameraOrbitBehaviour : public AbstractBehaviour
{
public:
	CameraOrbitBehaviour(const glm::vec3& distance, float tiltInDegrees, float rotationSpeed, GameObject* target);
	virtual ~CameraOrbitBehaviour();
	virtual void update(float step);

private:
	float rotationSpeed;
	GameObject* target;
	glm::mat4 rotateAroundTarget(float rotationsRadians, const glm::vec3& rotationAxis ) const;
	void mouseInput();
};

#endif
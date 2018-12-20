#ifndef CAMERAORBITBEHAVIOUR_HPP
#define CAMERAORBITBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/GameObject.hpp"

class CameraOrbitBehaviour : public AbstractBehaviour
{
public:
	CameraOrbitBehaviour(float distance, float tilt, float rotationSpeed, GameObject* target);
	virtual ~CameraOrbitBehaviour();
	virtual void update(float step);

private:
	float distance;
	float tilt;
	float rotationSpeed;
	GameObject* target;
};

#endif
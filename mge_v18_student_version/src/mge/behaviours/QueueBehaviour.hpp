#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"
#include "mge/Audio/AudioManager.hpp"

class QueueBehaviour : public AbstractBehaviour
{
public:
	QueueBehaviour();
	virtual ~QueueBehaviour();
	void update(float pStep);
	void lateUpdate(float pStep);
};
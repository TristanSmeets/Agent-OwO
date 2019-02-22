#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class EventQueueBehaviour : public AbstractBehaviour
{
public:
	EventQueueBehaviour();
	virtual ~EventQueueBehaviour();
	void update(float pStep);
	void lateUpdate(float pStep);
};
#include "QueueBehaviour.hpp"

QueueBehaviour::QueueBehaviour() : AbstractBehaviour()
{
}

QueueBehaviour::~QueueBehaviour()
{
}

void QueueBehaviour::update(float pStep)
{
}

void QueueBehaviour::lateUpdate(float pStep)
{
	EventQueue::DispatchEvents();
}

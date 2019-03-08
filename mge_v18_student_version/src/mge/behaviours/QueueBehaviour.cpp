#include "QueueBehaviour.hpp"

QueueBehaviour::QueueBehaviour() : AbstractBehaviour()
{
}

QueueBehaviour::~QueueBehaviour()
{
	std::cout << "GC running on:EventQueueBehaviour.\n";
}

void QueueBehaviour::update(float pStep)
{
}

void QueueBehaviour::lateUpdate(float pStep)
{
	EventQueue::DispatchEvents();
}

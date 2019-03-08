#include "EventQueueBehaviour.hpp"

EventQueueBehaviour::EventQueueBehaviour() : AbstractBehaviour()
{
}

EventQueueBehaviour::~EventQueueBehaviour()
{
	std::cout << "GC running on:EventQueueBehaviour.\n";
}

void EventQueueBehaviour::update(float pStep)
{
}

void EventQueueBehaviour::lateUpdate(float pStep)
{
	EventQueue::DispatchEvents();
}

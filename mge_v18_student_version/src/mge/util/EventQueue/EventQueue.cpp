#include "EventQueue.hpp"

int EventQueue::numberPending = 0;
std::vector<Observer*> EventQueue::observers;
EventInfo EventQueue::pending[maxQueueSize];

EventQueue::EventQueue()
{
	std::cout << "Creating EventQueue.\n";
}

EventQueue::~EventQueue()
{
	std::cout << "GC running on:EventQueue.\n";
	for (int index = 0; index < observers.size(); ++index)
	{
		observers[index] = nullptr;
	}
	observers.clear();
}

void EventQueue::AddObserver(Observer * observer)
{
	std::cout << "Adding Observer to EventQueue.\n";
	observers.push_back(observer);
}

void EventQueue::RemoveObserver(Observer * observer)
{
	std::cout << "Removing Observer From EventQueue.\n";
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void EventQueue::QueueEvent(const EventInfo & eventInfo)
{
	assert(numberPending < maxQueueSize);
	
	//Copy EventInfo data over.
	pending[numberPending] = eventInfo;

	numberPending++;
}

void EventQueue::DispatchEvents()
{
	//Looping over all queued events.
	for (int index = 0; index < numberPending; ++index)
	{
		//Loopinng over all observers.
		for (int observer = 0; observer < observers.size(); ++observer)
		{
			observers[observer]->OnNotify(pending[index]);
		}
	}
	//Resetting numberPending.
	numberPending = 0;
}

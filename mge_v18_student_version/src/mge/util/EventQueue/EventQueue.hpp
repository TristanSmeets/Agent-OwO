#pragma once

#include "mge/core/Observer.hpp"
#include <vector>
#include <algorithm>
#include <assert.h>

class EventQueue
{
public:
	static void AddObserver(Observer* observer);
	static void RemoveObserver(Observer* observer);
	static void QueueEvent(const EventInfo& eventInfo);
	static void DispatchEvents();

private:
	static int numberPending;
	static const int maxQueueSize = 20;
	static EventInfo pending[maxQueueSize];
	static std::vector<Observer*> observers;
};
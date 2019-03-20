#pragma once

#include "mge/core/Observer.hpp"
#include <vector>
#include <algorithm>
#include <assert.h>
#include "mge/util/EventQueue/EventStructs.hpp"

class EventQueue
{
public:
	static void AddObserver(Observer<GeneralEvent>* observer);
	static void RemoveObserver(Observer<GeneralEvent>* observer);
	static void QueueEvent(const GeneralEvent& eventInfo);
	static void DispatchEvents();

private:
	static int numberPending;
	static const int maxQueueSize = 20;
	static GeneralEvent pending[maxQueueSize];
	static std::vector<Observer<GeneralEvent>*> observers;
};
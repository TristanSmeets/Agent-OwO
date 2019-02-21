#pragma once

#include "mge/core/Observer.hpp"
#include <vector>
#include <algorithm>

class Subject
{
public:
	Subject();
	virtual ~Subject();
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void notify(const EventInfo& eventInfo);

private:
	std::vector<Observer*> observers;
};

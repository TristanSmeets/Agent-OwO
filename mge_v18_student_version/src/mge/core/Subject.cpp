#include "Subject.hpp"

Subject::Subject()
{
}

Subject::~Subject()
{
	std::cout << "GC running on:Subject\n";
	for (int index = 0; index < observers.size(); ++index)
	{
		observers[index] = nullptr;
	}
	observers.clear();
}

void Subject::AddObserver(Observer * observer)
{
	std::cout << "Adding Subcriber\n";
	observers.push_back(observer);
}

void Subject::RemoveObserver(Observer * observer)
{
	std::cout << "Removing Subscriber\n";
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(const EventInfo & eventInfo)
{
	for (unsigned int index = 0; index < observers.size(); ++index)
	{
		observers[index]->OnNotify(eventInfo);
	}
}


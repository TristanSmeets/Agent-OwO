#pragma once

#include "mge/core/Observer.hpp"
#include <vector>
#include <algorithm>
#include "mge/util/EventQueue/EventStructs.hpp"

template <typename T> class Subject
{
public:
	Subject(){};
	virtual ~Subject()
	{
		std::cout << "GC running on:Subject\n";
		for (int index = 0; index < observers.size(); ++index)
		{
			observers[index] = nullptr;
		}
		observers.clear();
	}
	
	void AddObserver(Observer<T>* observer)
	{
		std::cout << "Adding Subcriber\n";
		observers.push_back(observer);
	}

	void RemoveObserver(Observer<T>* observer)
	{
		std::cout << "Removing Subscriber\n";
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

protected:
	void notify(const T& eventInfo)
	{
		for (unsigned int index = 0; index < observers.size(); ++index)
		{
			observers[index]->OnNotify(eventInfo);
		}
	}

private:
	std::vector<Observer<T>*> observers;
};

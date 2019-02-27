#include "ButtonManager.hpp"

std::vector<Button*> ButtonManager::buttons;

ButtonManager::ButtonManager()
{
}

ButtonManager::~ButtonManager()
{
	std::cout << "GC running on:ButtonManager.\n";

	for (unsigned int index = 0; index < buttons.size(); ++index)
	{
		delete buttons[index];
	}
	buttons.clear();
}

void ButtonManager::AddButton(Button * button)
{
	buttons.push_back(button);
}

void ButtonManager::RemoveButton(Button * button)
{
	buttons.erase(std::remove(buttons.begin(), buttons.end(), button), buttons.end());
}

Button * ButtonManager::GetButton(int index)
{
	return buttons[index];
}

int ButtonManager::GetAmountOfButtons()
{
	return buttons.size();
}

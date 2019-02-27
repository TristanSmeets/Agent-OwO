#include "MouseInput.hpp"

MouseInput::MouseInput() : InputHandler()
{
	std::cout << "Creating MouseInput.\n";
}

MouseInput::~MouseInput()
{
	std::cout << "GC running on:MouseInput.\n";
}

Command * MouseInput::HandleInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (unsigned int index = 0; index <ButtonManager::GetAmountOfButtons(); ++index)
		{
		}
	}
	return nullptr;
}

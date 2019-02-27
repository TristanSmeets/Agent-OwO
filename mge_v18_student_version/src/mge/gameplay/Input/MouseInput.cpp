#include "MouseInput.hpp"

MouseInput::MouseInput(sf::Window* window) : InputHandler(), window(window)
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
			Button* current = ButtonManager::GetButton(index);
			if (isColliding(current))
			{
				std::cout << "Colliding with button\n.";
			}
		}
	}
	return nullptr;
}

bool MouseInput::isColliding(Button * button)
{
	glm::vec2 buttonPosition = button->GetPosition();
	glm::vec2 buttonSize = glm::vec2(button->GetSize().x * 0.5f, button->GetSize().y * 0.5f);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);

	return (mousePosition.y < buttonPosition.y + buttonSize.y &&	//Top
		mousePosition.y > buttonPosition.y - buttonSize.y &&	//Bottom
		mousePosition.x > buttonPosition.x - buttonSize.x &&	//Left
		mousePosition.x < buttonPosition.x + buttonSize.x);	//Right
}

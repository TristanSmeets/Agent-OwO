#include "MouseBehaviour.hpp"

MouseBehaviour::MouseBehaviour(sf::Window* window) : AbstractBehaviour()
{
	std::cout << "Creating MouseBehaviour.\n";
	mouseInput = MouseInput(window);
}

MouseBehaviour::~MouseBehaviour()
{
	std::cout << "GC running on:MouseBehaviour.\n";
}

void MouseBehaviour::update(float pStep)
{
	Command* command = mouseInput.HandleInput();

	if (command && buttonPressed == false)
	{
		std::cout << "Button pressed: " << buttonPressed << std::endl;
		command->Execute();
	}
	buttonPressed = command != nullptr;
}

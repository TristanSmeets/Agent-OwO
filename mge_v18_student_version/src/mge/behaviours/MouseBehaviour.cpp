#include "MouseBehaviour.hpp"

MouseBehaviour::MouseBehaviour(sf::Window* window) : AbstractBehaviour()
{
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
		command->Execute();
	}
	buttonPressed = command != nullptr;
}

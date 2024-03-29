#include "MouseBehaviour.hpp"

MouseBehaviour::MouseBehaviour(sf::Window* window) : AbstractBehaviour()
{
	mouseInput = MouseInput(window);
}

MouseBehaviour::~MouseBehaviour()
{
}

void MouseBehaviour::update(float pStep)
{
	Command* command = mouseInput.HandleInput();

	if (command && buttonPressed == false)
	{
		AudioLocator::GetAudio()->PlaySoundEffect(SFX_BUTTON);
		command->Execute();
	}
	buttonPressed = command != nullptr;
}

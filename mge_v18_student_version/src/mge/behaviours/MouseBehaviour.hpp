#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/gameplay/Input/MouseInput.hpp"
#include "mge/core/World.hpp"
#include "mge/Audio/AudioLocator.hpp"


class MouseBehaviour : public AbstractBehaviour
{
public:
	MouseBehaviour(sf::Window* window);
	~MouseBehaviour();
	void update(float pStep);
private:
	SoundEffect* soundEffect;
	MouseInput mouseInput;
	bool buttonPressed;
};

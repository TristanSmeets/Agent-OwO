#pragma once

#include "SFML/Window/Keyboard.hpp"
#include "mge/gameplay/Input/InputHandler.hpp"
#include "mge/behaviours/MovableBehaviour.hpp"
#include "mge/core/Observer.hpp"
#include "mge/util/EventQueue/EventQueue.hpp"

class PlayerInput : public InputHandler, public Observer<GeneralEvent>
{
public:
	PlayerInput(MovableBehaviour* movable);
	virtual ~PlayerInput();
	Command* HandleInput();
	void OnNotify(const GeneralEvent& info);
private:
	Command* moveUp;
	Command* moveDown;
	Command* moveLeft;
	Command* moveRight;
	bool buttonPressed;
	bool spacePressed;
	bool escPressed;
	bool canMove = false;
	bool showingPause = false;
};
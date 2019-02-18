#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/gameplay/InputHandler.hpp"

class MovableBehaviour : public AbstractBehaviour
{
public:
	MovableBehaviour(Node* startingNode);		//TODO: Add input handler
	~MovableBehaviour();
	Node* GetCurrentNode();
	void SetDestination(Node* node);
	InputHandler& GetInputHandler();
	virtual void update(float pStep);

private:
	Node* currentNode;
	void move();
	InputHandler inputHandler;
};
#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/gameplay/InputHandler.hpp"

class InputHandler;

class MovableBehaviour : public AbstractBehaviour
{
public:
	MovableBehaviour();
	MovableBehaviour(Node* startingNode);		//TODO: Add input handler
	~MovableBehaviour();
	Node* GetCurrentNode();
	void SetDestination(Node* node);
	void SetCurrentNode(Node* node);
	virtual void update(float pStep);

private:
	Node* currentNode;
	Node* destinationNode;
	void move();
	InputHandler* inputHandler;
};
#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/gameplay/Node.hpp"

class MovableBehaviour : public AbstractBehaviour
{
public:
	MovableBehaviour(Node* startingNode);		//TODO: Add input handler
	~MovableBehaviour();
	Node* GetCurrentNode();
	void SetDestination(Node* node);
	//TODO Add GetInputHandler()
	virtual void update(float pStep);

private:
	Node* currentNode;
	void move();
	//TODO: Add inputhandler
};
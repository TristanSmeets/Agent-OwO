#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/gameplay/Node.hpp"
#include "mge/gameplay/Input/InputHandler.hpp"

class InputHandler;

enum MOVABLE_TYPE { BOX_OBJECT, PLAYER_OBJECT };

class MovableBehaviour : public AbstractBehaviour
{
public:
	MovableBehaviour();
	MovableBehaviour(MOVABLE_TYPE movable);
	~MovableBehaviour();
	Node* GetCurrentNode();
	void SetDestination(Node* node);
	void SetCurrentNode(Node* node);
	virtual void update(float pStep);
	void move();
	MOVABLE_TYPE GetMovableType();

private:
	Node* currentNode;
	Node* destinationNode;
	InputHandler* inputHandler;
	bool buttonPushed;
	MOVABLE_TYPE movableType;
};
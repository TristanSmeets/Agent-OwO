#include "MovableBehaviour.hpp"
#include <iostream>

MovableBehaviour::MovableBehaviour(Node * startingNode) : currentNode(startingNode)
{
	std::cout << "Creating MovableBehaviour at:" << startingNode->GetPosition() << std::endl;
}

MovableBehaviour::~MovableBehaviour()
{
	AbstractBehaviour::~AbstractBehaviour();
	currentNode = nullptr;
}

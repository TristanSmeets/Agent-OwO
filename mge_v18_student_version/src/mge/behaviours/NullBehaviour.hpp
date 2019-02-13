#pragma once

#include "mge/behaviours/AbstractBehaviour.hpp"

class NullBehaviour : public AbstractBehaviour
{
public:
	NullBehaviour();
	~NullBehaviour();
	void update(float step);
};
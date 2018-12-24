#ifndef BROKENOBJ_HPP
#define BROKENOBJ_HPP

#include "mge/core/AbstractGame.hpp"

class BrokenOBJ : public AbstractGame
{
public:
	BrokenOBJ();
	virtual ~BrokenOBJ();
	virtual void initialize();

protected:
	virtual void _initializeScene();
	virtual void _render();

private:
	BrokenOBJ(const BrokenOBJ&);
	BrokenOBJ& operator= (const BrokenOBJ&);
};

#endif // !BROKENOBJ_HPP


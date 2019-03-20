#ifndef TRISTANSCENE_H
#define TRISTANSCENE_H

#include "mge/core/AbstractGame.hpp"

class TristanScene : public AbstractGame
{
public:
	TristanScene();
	virtual ~TristanScene();
	virtual void initialize();

protected:
	virtual void _initializeScene();
	virtual void _render();

private:
	TristanScene(const TristanScene&);
	TristanScene& operator=(const TristanScene&);

};
#endif 

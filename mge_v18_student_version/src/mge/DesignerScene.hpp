#ifndef DESIGNERSCENE_HPP
#define DESIGNERSCENE_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

class DesignerScene : public AbstractGame
{
public:
	DesignerScene();
	virtual ~DesignerScene();
	virtual void initialize();

protected:
	virtual void _initializeScene();
	virtual void _render();

private:
	DebugHud* hud;
	void updateHud();
};

#endif

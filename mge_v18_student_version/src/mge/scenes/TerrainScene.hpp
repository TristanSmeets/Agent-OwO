#ifndef TERRAINSCENE_HPP
#define TERRAINSCENE_HPP

#include "mge/core/AbstractGame.hpp"

class TerrainScene : public AbstractGame
{
public:
	TerrainScene();
	virtual ~TerrainScene();
	virtual void initialize();

protected:
	virtual void _initializeScene();
	virtual void render();

private:
	TerrainScene(const TerrainScene&);
};

#endif

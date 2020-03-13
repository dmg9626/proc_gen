#pragma once
#include "TileMap.h"
class TerrainPass
{
public:
	/* Finds any instances of find_tile without any neighbors of the same type and replaces them with replace_tile*/
	void CleanUpPatches(TileMap* tilemap, int find_tile, int replace_tile);

	/* Converts any land tiles bordering water to sand tiles */
	void AddSand(TileMap* tilemap);
private:
	/* Returns true if tile at (x,y) has neighbors of the given type */
	bool HasNeighborsOfType(int x, int y, TileMap* tilemap, int tile_type);
	
};


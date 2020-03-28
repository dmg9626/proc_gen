#pragma once
#include <stdlib.h>
#include <cmath>
#include "TileMap.h"
using namespace std;
class TerrainPass
{
public:
	/* Calculates water level for heightmap based on desired ratio (percentage between 0 and 1) of water to land*/
	float CalculateWaterLevel(float** heightmap, int size, float waterRatio);

	/* Finds any instances of find_tile without any neighbors of the same type and replaces them with replace_tile*/
	void CleanUpPatches(TileMap* tilemap, int find_tile, int replace_tile);

	/* Converts any land tiles bordering water to sand tiles */
	void AddSand(TileMap* tilemap);

	/* Populates land with trees (amount corresponding to treeRatio between 0-1)*/
	void PopulateTrees(TileMap * terrainLayer, TileMap* objectLayer, float treeRatio);
private:
	/* Returns true if tile at (x,y) has neighbors of the given type */
	bool HasNeighborsOfType(int x, int y, TileMap* tilemap, int tile_type);

	/* Returns random float value between 0 and 1 (inclusive) */
	float rand01() {
		// TODO: rewrite this - the first value returned is always the same
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
	
};


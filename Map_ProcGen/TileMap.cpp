#include "TileMap.h"
#include <stdio.h>

int TileMap::GetTileAt(int x, int y)
{
	return _rows[y][x];
}

void TileMap::SetTileAt(int x, int y, int tile_type)
{
	_rows[y][x] = tile_type;
}

void TileMap::InitFromHeightmap(float** heightmap, float water_level)
{
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) 
		{
			// Assign each tile based on height value
			float height = heightmap[y][x];
			if (height < water_level)
				_rows[y][x] = WATER_TILE;
			else
				_rows[y][x] = LAND_TILE;
		}
	}
}


void TileMap::Print()
{
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (GetTileAt(x, y) == LAND_TILE)
				printf("#");
			else if (GetTileAt(x, y) == WATER_TILE)
				printf("~");
		}
		printf("\n");
	}
}
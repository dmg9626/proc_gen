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
	// Print x labels on top
	printf("\n\t");
	for (int x = 0; x < 10; x++) {
		printf("%d", x);
	}
	printf("\n");
	for (int y = 0; y < size; y++) {
		printf("%d\t", y);
		for (int x = 0; x < size; x++) {
			if (GetTileAt(x, y) == LAND_TILE)
				printf("#");
			else if (GetTileAt(x, y) == WATER_TILE)
				printf("~");
		}
		printf("\n");
	}

	// Print x labels on bottom
	printf("\t");
	for (int x = 0; x < 10; x++) {
		printf("%d", x);
	}
}
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

void TileMap::AllocateGrid(int _size)
{
	size = _size;
	if (size < 1)
		return;

	// Allocate pointer array to hold each row
	_rows = new int* [size];
	for (int i = 0; i < size; i++) {
		// Allocate each row with empty values
		_rows[i] = new int[size];
		for (int j = 0; j < size; j++) {
			_rows[i][j] = -1;
		}
	}
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

bool TileMap::FindTileByType(int tile_type, int& out_x, int& out_y)
{
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (GetTileAt(x, y) == tile_type) {
				out_x = x;
				out_y = y;
				return true;
			}
		}
	}
	return false;
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
		for (int x = 0; x < size; x++) 
		{
			switch (GetTileAt(x, y)) {
			case LAND_TILE:
				printf("#");
				break;
			case WATER_TILE:
				printf("~");
				break;
			case SAND_TILE:
				printf(".");
				break;
			case TREE_TILE:
				printf("^");
				break;
			default:
				printf(" ");
				break;
			}
		}
		printf("\n");
	}

	// Print x labels on bottom
	printf("\t");
	for (int x = 0; x < 10; x++) {
		printf("%d", x);
	}
}
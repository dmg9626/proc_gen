#include "TerrainPass.h"
#include <stdio.h>

float TerrainPass::CalculateWaterLevel(float** heightmap, int size, float waterRatio)
{
	// Find average altitude
	float sum = 0;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			sum += heightmap[y][x];
		}
	}
	float avg = sum / pow(size, 2);

	// Scale that by desired water ratio
	return avg * waterRatio;
}

void TerrainPass::CleanUpPatches(TileMap* tilemap, int find_tile, int replace_tile)
{
	// Iterate over each row
	for (int y = 0; y < tilemap->size; y++)
	{
		for (int x = 0; x < tilemap->size; x++)
		{
			int tile = tilemap->GetTileAt(x, y);

			// Skip if tile isn't specified type
			if (tile != find_tile)
				continue;

			// If tile has no neighbors of same type, replace with replace_tile
			if (!HasNeighborsOfType(x, y, tilemap, find_tile)) {
				tilemap->SetTileAt(x, y, replace_tile);
			}
		}
	}
}

bool TerrainPass::HasNeighborsOfType(int x, int y, TileMap *tilemap, int tile_type)
{
	// Left of tile
	if (x > 0) {
		// Left
		if (tilemap->GetTileAt(x - 1, y) == tile_type)
			return true;
		// Upper left
		if (y > 0 && tilemap->GetTileAt(x - 1, y - 1) == tile_type)
			return true;
		// Lower left
		if (y < tilemap->size - 1 && tilemap->GetTileAt(x - 1, y + 1) == tile_type)
			return true;
	}

	// Right of tile
	if (x < tilemap->size - 1) {
		// Right
		if (tilemap->GetTileAt(x + 1, y) == tile_type)
			return true;
		// Upper right
		else if (y > 0 && tilemap->GetTileAt(x + 1, y - 1) == tile_type)
			return true;
		// Lower right
		else if (y < tilemap->size - 1 && tilemap->GetTileAt(x + 1, y + 1) == tile_type)
			return true;
	}

	// Above/Below
	if(y > 0 && tilemap->GetTileAt(x, y - 1) == tile_type)
		return true;
	if (y < tilemap->size - 1 && tilemap->GetTileAt(x, y + 1) == tile_type)
		return true;

	else return false;
}

void TerrainPass::AddSand(TileMap* tilemap)
{
	// Iterate over each row
	for (int y = 0; y < tilemap->size; y++) {
		for (int x = 0; x < tilemap->size; x++) {
			int tile = tilemap->GetTileAt(x, y);

			// Skip if tile isn't specified type
			if (tile != LAND_TILE)
				continue;

			// If land tile is bordering water, change it to sand
			if (HasNeighborsOfType(x, y, tilemap, WATER_TILE)) {
				tilemap->SetTileAt(x, y, SAND_TILE);
			}
		}
	}
}

void TerrainPass::PopulateTrees(TileMap* terrainLayer, TileMap* objectLayer, float treeRatio)
{
	// Iterate over each tile in terrain layer
	for (int y = 0; y < terrainLayer->size; y++) {
		for (int x = 0; x < terrainLayer->size; x++) {
			int tile = terrainLayer->GetTileAt(x, y);

			// Skip if tile isn't specified type
			if (tile != LAND_TILE)
				continue;

			// Randomly place trees on objectLayer based on treeRatio chance
			float chance = rand01();
			if (chance < treeRatio) {
				objectLayer->SetTileAt(x, y, TREE_TILE);
			}
		}
	}
}
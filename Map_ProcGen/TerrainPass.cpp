#include "TerrainPass.h"
#include <stdio.h>

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
			if (!HasNeighborsOfType(x, y, *tilemap, find_tile)) {
				printf("Tile (%d, %d) has no neighboring tiles of type %d\n", x, y, find_tile);
				tilemap->SetTileAt(x, y, replace_tile);
			}
		}
	}
}

bool TerrainPass::HasNeighborsOfType(int x, int y, TileMap tilemap, int tile_type)
{
	if (x == 6 && y == 0) {
		printf("flag\n");
	}
	// Left of tile
	if (x > 0) {
		// Left
		if (tilemap.GetTileAt(x - 1, y) == tile_type)
			return true;
		// Upper left
		if (y > 0 && tilemap.GetTileAt(x - 1, y - 1) == tile_type)
			return true;
		// Lower left
		if (y < tilemap.size - 1 && tilemap.GetTileAt(x - 1, y + 1) == tile_type)
			return true;
	}

	// Right of tile
	if (x < tilemap.size - 1) {
		// Right
		if (tilemap.GetTileAt(x + 1, y) == tile_type)
			return true;
		// Upper right
		else if (y > 0 && tilemap.GetTileAt(x + 1, y - 1) == tile_type)
			return true;
		// Lower right
		else if (y < tilemap.size - 1 && tilemap.GetTileAt(x + 1, y + 1) == tile_type)
			return true;
	}

	// Above/Below
	if(y > 0 && tilemap.GetTileAt(x, y - 1) == tile_type)
		return true;
	if (y < tilemap.size - 1 && tilemap.GetTileAt(x, y + 1) == tile_type)
		return true;

	else return false;
}

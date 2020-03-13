#pragma once
class TileMap
{
public:
	TileMap(int _size)
	{
		AllocateGrid(_size);
	}

	TileMap(float** heightmap, int _size, float water_level)
	{
		AllocateGrid(_size);

		// Populate rows with tiles based on heightmap values
		InitFromHeightmap(heightmap, water_level);
	};

	~TileMap(){};

	/* Returns tile at (x,y) */
	int GetTileAt(int x, int y);

	/* Sets tile at (x,y) to given tile type */
	void SetTileAt(int x, int y, int tile_type);

	/* Searches the map for a tile of given type and assigns coordinates to x and y. Returns true if matching tile found */
	bool FindTileByType(int tile_type, int& x, int& y);

	/** Prints text-representation of tilemap */
	void Print();

	int size;

private:
	int** _rows;

	void AllocateGrid(int _size);

	void InitFromHeightmap(float** heightmap, float water_level);
};

static int LAND_TILE = 31;
static int WATER_TILE = 21;
static int SAND_TILE = 41;
static int TREE_TILE = 45;
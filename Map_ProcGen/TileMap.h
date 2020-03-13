#pragma once
class TileMap
{
public:
	TileMap(float** heightmap, int _size, float water_level)
	{
		size = _size;
		if (size < 1)
			return;

		// Allocate pointer array to hold each row
		_rows = new int* [size];
		for (int i = 0; i < size; i++) {
			// Allocate each row
			_rows[i] = new int[size];
		}

		// Populate rows with tiles based on heightmap values
		InitFromHeightmap(heightmap, water_level);
	};

	~TileMap(){};

	/* Returns tile at (x,y) */
	int GetTileAt(int x, int y);

	/** Sets tile at (x,y) to given tile type */
	void SetTileAt(int x, int y, int tile_type);

	/** Prints text-representation of tilemap */
	void Print();

	int size;

private:
	int** _rows;

	void InitFromHeightmap(float** heightmap, float water_level);
};

static int LAND_TILE = 31;
static int WATER_TILE = 21;
static int SAND_TILE = 41;
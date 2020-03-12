#pragma once
class TileMap
{
public:
	TileMap(float** heightmap, int size, float water_level)
	{
		_size = size;
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

	int Size() {
		return _size;
	}

	/** Prints text-representation of tilemap */
	void Print();


private:
	int** _rows;
	int _size;

	void InitFromHeightmap(float** heightmap, float water_level);
};

static int LAND_TILE = 31;
static int WATER_TILE = 21;

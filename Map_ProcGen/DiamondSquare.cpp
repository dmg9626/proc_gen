#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(int size)
{
	// Initialize heightmap if not provided
	float** rows = new float*[size - 1];
	for (int i = 0; i < size - 1; i++) 
	{
		rows[i] = new float[size - 1];
		for (int j = 0; j < size - 1; j++) 
		{
			rows[i][j] = 0;
		}
	}

	// TODO: generate heightmap here

	// Return generated heightmap array
	return rows;
}
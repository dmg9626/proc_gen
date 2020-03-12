#include <iostream>
#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(int n)
{
	if (n < 1)
		return nullptr;

	int size = pow(2, n) + 1;
	printf("Generating map of size %d", size);

	// Initialize heightmap if not provided
	float** rows = new float*[size];
	for (int i = 0; i < size; i++) 
	{
		rows[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			rows[i][j] = 0;
		}
	}

	// TODO: generate heightmap here

	// Return generated heightmap array
	return rows;
}
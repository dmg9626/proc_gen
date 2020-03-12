#include <iostream>
#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(int n)
{
	if (n <= 1)
		return nullptr;

	// TODO: pass in srand() seed to method and set it here

	// Initialize empty heightmap
	int size = pow(2, n) + 1;
	float** rows = InitializeFloatArray(size);

	// Set random values in corners of map
	float* topRow = rows[0];
	float* bottomRow = rows[size - 1];

	topRow[0] = rand01();
	topRow[size - 1] = rand01();
	bottomRow[0] = rand01();
	bottomRow[size - 1] = rand01();
	
	// TODO: generate heightmap here

	// Return generated heightmap array
	return rows;
}

float** DiamondSquare::InitializeFloatArray(int size)
{
	printf("Generating map of size %d\n\n", size);

	// Allocate pointer array to hold each row
	float** rows = new float* [size];
	for (int i = 0; i < size; i++) 
	{
		// Allocate each row
		rows[i] = new float[size];

		// Set each value in the row to 0
		for (int j = 0; j < size; j++) {
			rows[i][j] = 0;
		}
	}
	return rows;
}
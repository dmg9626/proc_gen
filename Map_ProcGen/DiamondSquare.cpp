#include <iostream>
#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(int n)
{
	if (n < 1)
		return nullptr;

	// Initialize empty heightmap
	float** rows = InitializeFloatArray(n);

	// TODO: generate heightmap here

	// Return generated heightmap array
	return rows;
}

float** DiamondSquare::InitializeFloatArray(int n)
{
	int size = pow(2, n) + 1;
	printf("Generating map of size %d", size);

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
#include <iostream>
#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(const int n)
{
	if (n <= 1)
		return nullptr;

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
	
	for (int i = 0; i < n; i++) {
		// Populate values across map in increasingly granular steps
		int step = pow(2, n-i) / 2;
		printf("Step size: %d\n", step);

		// SQUARE
		Square(size, step, rows);

		// DIAMOND
		Diamond(size, step, rows);
	}

	// Return generated heightmap array
	return rows;
}

void DiamondSquare::Diamond(const int size, const int step, float** heightmap)
{
	// TODO: halve noise after each iteration
	float noise = .1f;

	// Iterate over rows
	for (int y = step; y < size-1; y += step) 
	{
		// Iterate over items in row
		float* row = heightmap[y];
		for (int x = step; x < size - 1; x += step) 
		{
			// Get average of diagonally-neighboring values at step distance
			float topLeft = heightmap[y - step][x - step];
			float topRight = heightmap[y - step][x + step];
			float bottomLeft = heightmap[y + step][x - step];
			float bottomRight = heightmap[y + step][x + step];

			float avg = (topLeft + topRight + bottomLeft + bottomRight) / 4;
			//printf("neighbors: %.2f, %.2f, %.2f, %.2f\n", topLeft, topRight, bottomLeft, bottomRight);
			//printf("average: %.2f\n", avg);

			// Set tile value to avg + noise
			row[x] = avg + (avg * noise);
		}
	}
}

void DiamondSquare::Square(const int size, const int step, float** heightmap)
{

}

float** DiamondSquare::InitializeFloatArray(const int size)
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
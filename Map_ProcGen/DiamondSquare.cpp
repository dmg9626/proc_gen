#include <iostream>
#include "DiamondSquare.h"

float** DiamondSquare::GenerateHeightMap(const int n, const int seed)
{
	if (n <= 1)
		return nullptr;

	// Set random seed and call it once so we get true randoms
	srand(seed);
	rand01();

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
	
	// Noise applied to each diamond-square operation (halved after each iteration)
	float noise = .25f;
	for (int i = 0; i < n; i++) 
	{
		// Populate values across map in increasingly granular steps
		int step = pow(2, n-i) / 2;

		Diamond(size, step, rows, noise);
		Square(size, step, rows, noise);

		// Halve noise and repeat
		noise /= 2;
	}

	// Return generated heightmap array
	return rows;
}

void DiamondSquare::Diamond(const int size, const int step, float** heightmap, const float noise)
{
	// Iterate over rows
	for (int y = step; y < size-1; y += step) 
	{
		// Iterate over items in row
		for (int x = step; x < size - 1; x += step) 
		{
			// Get average of diagonally-neighboring values at step distance
			float topLeft = heightmap[y - step][x - step];
			float topRight = heightmap[y - step][x + step];
			float bottomLeft = heightmap[y + step][x - step];
			float bottomRight = heightmap[y + step][x + step];

			float avg = (topLeft + topRight + bottomLeft + bottomRight) / 4;

			// Set tile value to avg + random noise
			float rand_noise = (rand01() / 2) * noise;
			heightmap[y][x] = avg + (avg * rand_noise);
		}
	}
}

void DiamondSquare::Square(const int size, const int step, float** heightmap, const float noise)
{
	// PASS 1
	for (int y = 0; y < size; y += step * 2) {
		for (int x = step; x < size; x += step * 2) {
			// Get average of neighbors
			float avg = NeighborAverageSquare(x, y, size, step, heightmap);

			// Set tile value to avg + random noise
			float rand_noise = (rand01() / 2) * noise;
			heightmap[y][x] = avg + (avg * rand_noise);
		}
	}

	// PASS 2
	for (int y = step; y < size; y += step * 2) {
		for (int x = 0; x < size; x += step * 2) {
			// Get average of neighbors
			float avg = NeighborAverageSquare(x, y, size, step, heightmap);

			// Set tile value to avg + random noise
			float rand_noise = (rand01() / 2) * noise;
			heightmap[y][x] = avg + (avg * rand_noise);
		}
	}
}

float DiamondSquare::NeighborAverageSquare(const int x, const int y, const int size, const int step, float** heightmap)
{
	float topNeighbor = 0, bottomNeighbor = 0, leftNeighbor = 0, rightNeighbor = 0;

	// Track number of neighbors while checking their values
	int neighboutCount = 0;
	if (x + step < size) {
		rightNeighbor = heightmap[y][x + step];
		neighboutCount++;
	}
	if (x - step >= 0) {
		leftNeighbor = heightmap[y][x - step];
		neighboutCount++;
	}
	if (y + step < size) {
		bottomNeighbor = heightmap[y + step][x];
		neighboutCount++;
	}
	if (y - step >= 0) {
		topNeighbor = heightmap[y - step][x];
		neighboutCount++;
	}

	// Calculate average
	float avg = (topNeighbor + bottomNeighbor + leftNeighbor + rightNeighbor) / neighboutCount;
	return avg;
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
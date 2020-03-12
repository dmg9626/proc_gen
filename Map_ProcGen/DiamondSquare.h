#pragma once
#include <cmath>

class DiamondSquare
{
public:
	/* Returns a 2D float array representing a heightmap of size 2^(n) + 1 */
	float** GenerateHeightMap(const int n);

	void PrintHeightMap(float** heightmap, const int size)
	{
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%.2f\t", heightmap[i][j]);
			}
			printf("\n\n");
		}
	}

private:
	/* Performs diamond step of algorithm */
	void Diamond(const int size, const int step, float** heightmap, const float noise);
	
	/* Performs square step of algorithm */
	void Square(const int size, const int step, float** heightmap, const float noise);

	/* Returns average of neighbors of (x,y) within step-sized square on heightmap */
	float NeighborAverageSquare(const int x, const int y, const int size, const int step, float** heightmap);

	/* Returns a properly-sized float array of zeroes */
	float** InitializeFloatArray(const int size);

	/* Returns random float value between 0 and 1 (inclusive) */
	float rand01() {
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
	
	/* Returns true if point (x,y) is at the edge of a map of given size */
	bool IsEdgePoint(const int x, const int y, const int size)
	{
		return (x == 0 || x == size - 1 || y == 0 || y == size - 1);
	}
};

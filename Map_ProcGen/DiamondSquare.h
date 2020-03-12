#pragma once
#include <cmath>

class DiamondSquare
{
public:
	/* Returns a 2D float array representing a heightmap of size 2^(n) + 1 */
	float** GenerateHeightMap(const int n);

private:
	/* Performs diamond step of algorithm */
	void Diamond(const int size, const int step, float** heightmap, const float noise);
	
	/* Performs square step of algorithm */
	void Square(const int size, const int step, float** heightmap, const float noise);

	/* Returns a properly-sized float array of zeroes */
	float** InitializeFloatArray(const int size);

	/* Returns random float value between 0 and 1 (inclusive) */
	float rand01() {
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}
};

#pragma once
#include <cmath>

class DiamondSquare
{
public:
	/* Returns a 2D float array representing a heightmap of size 2^(n) + 1 */
	float** GenerateHeightMap(int n);

private:
	/* Performs diamond step of algorithm */
	void Diamond(int size, int step, float** heightmap);
	
	/* Performs square step of algorithm */
	void Square(int size, int step, float** heightmap);

	/* Returns a properly-sized float array of zeroes */
	float** InitializeFloatArray(int n);
};

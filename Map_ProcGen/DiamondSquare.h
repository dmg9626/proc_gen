#pragma once
class DiamondSquare
{
public:
	/* Returns a 2D float array representing a heightmap of size 2^(size-1) */
	float** GenerateHeightMap(int size);

private:
	/* Performs diamond step of algorithm */
	void Diamond(int size, int step, float** heightmap);
	
	/* Performs square step of algorithm */
	void Square(int size, int step, float** heightmap);
};

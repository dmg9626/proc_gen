#include <iostream>
#include "DiamondSquare.h"


int SIZE = 5;
int main()
{
    DiamondSquare diamondSquare;
    float** heightmap = diamondSquare.GenerateHeightMap(SIZE);

    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            printf("%f ", heightmap[i][j]);
        }
        printf("\n");
    }
}
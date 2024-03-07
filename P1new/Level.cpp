#include "Level.h"
using namespace std;

typedef vector<vector<Wall>> Matrix;
typedef vector<Wall> Row;

Level::Level(int width, int height):width(width), height(height) {
    for (size_t i = 0; i < width; ++i)
    {
        Row row(width);

        for (size_t j = 0; j < height; ++j)
        {
            Wall wall;
            row[j] = wall;
        }

        walls.push_back(row); // push each row after you fill it
    }
}
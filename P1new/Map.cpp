#include "Map.h"
#include "Level.h"
#include <vector>
using namespace std;

Map::Map(int width, int height, sf::Clock clock){
    for (size_t i = 0; i < width; ++i)
    {
        for (size_t j = 0; j < height; ++j)
        {
            Level level;
            levels.push_back(level);
        }
    }
};

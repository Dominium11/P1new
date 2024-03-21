#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Level.h"
#include <vector>

using namespace std;

class Level;

#ifndef MAP_HEADER_
#define MAP_HEADER_

class Map
{
public:
	Map(int width, int height, sf::Clock clock);
	std::vector<Level> levels;
};

#endif
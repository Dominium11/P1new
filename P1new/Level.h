#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Enemy.h"
#include <vector>

class Enemy;

typedef std::vector<std::vector<Wall>> Matrix;
typedef std::vector<Wall> Row;

class Level
{
	public:
		Level(int width, int height);
		int width, height;
		Matrix walls;
		std::vector<Enemy> enemies;
};
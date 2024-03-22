#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Enemy.h"
#include <vector>

class Enemy;

class Level
{
	public:
		Level();
		std::vector<Wall> walls;
};
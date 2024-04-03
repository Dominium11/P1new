#pragma once

#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "TileMap.h"
#include "Enemy.h"

class EnemyMap;

#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_

class Player
{
	public:
		double movementSpeed = 10;
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		Player(std::string spritePath, int sizeX, int sizeY, int posX, int posY, sf::Clock &clock);
		void Update(sf::RenderWindow& window, TileMap map[], sf::View playerView, EnemyMap &eMap);
		sf::Vector2f getPosition();
	private:
		//Resolves collision with sf::Shape objects by taking current movement axis
		sf::Clock clock;
		void resolveCollision(sf::FloatRect collisionNormal, sf::FloatRect);
		sf::Texture texture;
		int sizeX, sizeY;
		short int horizontal = 0, vertical = 0;
		const double diagMod = 0.707106; ///Sin(45) to make angular movement match non-angular movement
};

#endif

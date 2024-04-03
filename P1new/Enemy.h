#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

class Player;

#ifndef ENEMY
#define ENEMY

class EnemyMap : public sf::Drawable, public sf::Transformable
{
public:
	EnemyMap();
	sf::VertexArray getVertices();
	bool pushNewEnemy(const std::string& tileset, sf::Vector2u tileSize, int tiles, int posX, int posY);
	void Update(sf::RenderWindow& window, sf::View playerView, Player player, TileMap map[]);
	void deleteEnemy(int verticeIndex);
	int getAmountOfEnemies();
private:
	sf::Vector2f normalize(sf::Vector2f);
	int amountOfEnemies = 0;
	int speed = 1;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	int posX, posY;
};

#endif



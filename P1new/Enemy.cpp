#include "Enemy.h"
#include <string>
#include <math.h>
#include <iostream>
using namespace sf;

Enemy::Enemy(std::string spritePath, int sizeX, int sizeY, int posX, int posY, sf::Clock& clock) :
	sizeY(sizeY), sizeX(sizeX), clock(clock)
{
	hitbox.setPosition(posX, posY);
	hitbox.setSize(sf::Vector2f(sizeX, sizeY));
	movementSpeed = 5;
	health = 100;
	if (!texture.loadFromFile(spritePath))
	{
		throw std::invalid_argument("Missing file/Invalid path to Player sprite specified");
	}
	else {
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}
};

void Enemy::Update(sf::RenderWindow& window, Level level) {
	horizontal = 0;
	vertical = 0;

	if (Keyboard::isKeyPressed(Keyboard::J)) horizontal -= 1;
	if (Keyboard::isKeyPressed(Keyboard::L)) horizontal += 1;
	if (Keyboard::isKeyPressed(Keyboard::I)) vertical -= 1;
	if (Keyboard::isKeyPressed(Keyboard::K)) vertical += 1;


	/* ENEMY MOVEMENT HERE
	if (Keyboard::isKeyPressed(Keyboard::A)) horizontal -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D)) horizontal += 1;
	if (Keyboard::isKeyPressed(Keyboard::W)) vertical -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) vertical += 1;
	*/

	if (horizontal != 0 && vertical != 0) {
		sprite.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
		hitbox.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
	}
	else {
		sprite.move(horizontal * movementSpeed, vertical * movementSpeed);
		hitbox.move(horizontal * movementSpeed, vertical * movementSpeed);
	}

	sf::FloatRect overlap;
	sf::FloatRect enemyBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
	for (int i = 0; i < level.walls.size(); i++)
	{
		sf::FloatRect collisionNormal;
		for (int j = 0; j < level.walls.size(); j++)
		{
			if (level.walls[i][j].collider.getGlobalBounds().intersects(enemyBounds, overlap)) {
				collisionNormal = overlap;
				resolveCollision(overlap, level.walls[i][j].collider);
				enemyBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
			}
		}
	}
};

void Enemy::resolveCollision(sf::FloatRect collisionNormal, sf::RectangleShape collided) {
	sf::Vector2f colSize = collisionNormal.getSize();
	sf::Vector2f enemyPos = hitbox.getPosition();
	sf::Vector2f collidedPos = collided.getPosition();
	colSize.x = -colSize.x;
	colSize.y = -colSize.y;

	if (horizontal != 0 && vertical != 0) {
		if (colSize.x <= colSize.y) {		//Colliding from top/bottom diagonal
			this->sprite.move(0, colSize.y * vertical);
			this->hitbox.move(0, colSize.y * vertical);
		}
		else if (colSize.x >= colSize.y) {		//Colliding from left/right diagonal
			this->sprite.move(colSize.x * horizontal, 0);
			this->hitbox.move(colSize.x * horizontal, 0);
		}
	}
	else {
		if (vertical == 0 && horizontal != 0) { //Colliding from left/right
			this->sprite.move(colSize.x * horizontal, 0);
			this->hitbox.move(colSize.x * horizontal, 0);
		}
		else if (horizontal == 0 && vertical != 0) { //Colliding from top/bottom
			this->sprite.move(0, colSize.y * vertical);
			this->hitbox.move(0, colSize.y * vertical);
		}
	}
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	target.draw(hitbox);
	target.draw(sprite);
}
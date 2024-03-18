#include "Player.h"
#include <string>
#include <math.h>
#include <iostream>

using namespace sf;

Player::Player(std::string spritePath, int sizeX, int sizeY, int posX, int posY, sf::Clock& clock) :
sizeY(sizeY), sizeX(sizeX), clock(clock)
{
	hitbox.setPosition(posX, posY);
	hitbox.setSize(sf::Vector2f(sizeX, sizeY));
	movementSpeed = 5;
	if (!texture.loadFromFile(spritePath))
	{
		throw std::invalid_argument("Missing file/Invalid path to Player sprite specified");
	}
	else {
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}
};

void Player::Update(sf::RenderWindow &window, Level level) {
	horizontal = 0;
	vertical = 0;
	if (Keyboard::isKeyPressed(Keyboard::A)) horizontal -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D)) horizontal += 1;
	if (Keyboard::isKeyPressed(Keyboard::W)) vertical -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) vertical += 1;

	if (horizontal != 0 && vertical != 0) {
		sprite.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
		hitbox.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
	}
	else {
		sprite.move(horizontal * movementSpeed, vertical * movementSpeed);
		hitbox.move(horizontal * movementSpeed, vertical * movementSpeed);
	}

	sf::FloatRect overlap;
	sf::FloatRect playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
	for (int i = 0; i < level.walls.size(); i++)
	{
		sf::FloatRect collisionNormal;
		for (int j = 0; j < level.walls[i].size(); j++)
		{
			if(level.walls[i][j].collider.getGlobalBounds().intersects(playerBounds, overlap)){
				collisionNormal = overlap;
				resolveCollision(overlap, level.walls[i][j].collider);
				playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
			}
		}
	}
	for (Enemy enemy : level.enemies) {
		sf::FloatRect collisionNormal;
		if (enemy.hitbox.getGlobalBounds().intersects(playerBounds, overlap)) {
			collisionNormal = overlap;
			resolveCollision(overlap, enemy.hitbox);
			playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
		}
	}
};

void Player::resolveCollision(sf::FloatRect collisionNormal, sf::RectangleShape collided) {
	sf::Vector2f colSize = collisionNormal.getSize();
	sf::Vector2f playerPos = hitbox.getPosition();
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



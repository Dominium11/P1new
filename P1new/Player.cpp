#include "Player.h"
#include "Wall.h"
#include <string>
#include <math.h>
#include <iostream>

using namespace sf;

Player::Player(std::string spritePath, int sizeX, int sizeY, int posX, int posY):
sizeY(sizeY), sizeX(sizeX)
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

void Player::Update(sf::RenderWindow &window, std::vector<std::vector<Wall>>&walls) {
	horizontal = 0;
	vertical = 0;
	if (Keyboard::isKeyPressed(Keyboard::A)) horizontal -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D)) horizontal += 1;
	if (Keyboard::isKeyPressed(Keyboard::W)) vertical -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) vertical += 1;

	if (horizontal != 0 && vertical != 0) {
		this->sprite.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
		this->hitbox.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
	}
	else {
		this->sprite.move(horizontal * movementSpeed, vertical * movementSpeed);
		this->hitbox.move(horizontal * movementSpeed, vertical * movementSpeed);
	}

	sf::FloatRect overlap;
	sf::FloatRect playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
	for (int i = 0; i < walls.size(); i++)
	{
		sf::FloatRect collisionNormal;
		for (int j = 0; j < walls[i].size(); j++)
		{
			if (walls[i][j].collider.getGlobalBounds().intersects(playerBounds, overlap)) {
				collisionNormal = overlap;
				resolveCollision(overlap, walls[i][j].collider);
			}
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
		if (colSize.x <= colSize.y) {		//Colliding from top/bottom
			this->sprite.move(0, colSize.y * vertical);
			this->hitbox.move(0, colSize.y * vertical);
		}
		else if (colSize.x >= colSize.y) {		//Colliding from left/right
			this->sprite.move(colSize.x * horizontal, 0);
			this->hitbox.move(colSize.x * horizontal, 0);
		}
	}
	else {
		if (vertical == 0 && horizontal != 0) {
			this->sprite.move(colSize.x * horizontal, 0);
			this->hitbox.move(colSize.x * horizontal, 0);
		}
		else if (horizontal == 0 && vertical != 0) {
			this->sprite.move(0, colSize.y * vertical);
			this->hitbox.move(0, colSize.y * vertical);
		}
	}
}



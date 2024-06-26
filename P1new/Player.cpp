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

void Player::Update(sf::RenderWindow &window, TileMap map[], sf::View playerView, EnemyMap &eMap) {
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

	sf::Vector2f viewCenter(playerView.getCenter());
	sf::Vector2f viewSize(playerView.getSize());
	sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);

	sf::FloatRect overlap;
	sf::FloatRect collisionNormal;
	sf::FloatRect playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
	
	for (int m = 0; m < 36; m++) {
		TileMap level = map[m];
		int offset = -1;
		for (int i = 0; i < level.getVertices().getVertexCount(); i += 6) {
			std::vector<int> tileIds = level.getTileIds();
			int tileId = tileIds[((level.height * (i / 6)) % (level.width * level.height)) + offset];
			if (tileId != 0) {
				if (((i / 6) % level.width == 0)) {
					offset += 1;
				}
				continue;
			}
			sf::VertexArray vertices = level.getVertices();
			if (((i / 6) % level.width == 0)) {
				offset += 1;
			}
			sf::FloatRect boundingBox(vertices[i].position.x, vertices[i].position.y, vertices[i + 1].position.x - vertices[i].position.x, vertices[i + 2].position.y - vertices[i].position.y);
			if (boundingBox.intersects(currentViewRect)) {
				if (boundingBox.intersects(playerBounds, overlap) && tileId == 0) {
					collisionNormal = overlap;
					resolveCollision(overlap, boundingBox);
					playerBounds = hitbox.getTransform().transformRect(hitbox.getLocalBounds());
				}
			}
		}
	}
	for (int m = 0; m < eMap.getVertices().getVertexCount(); m+=6) {
		std::cout << " GOT HERE " << std::endl;
		sf::VertexArray vertices = eMap.getVertices();
		sf::FloatRect boundingBox(vertices[m].position.x, vertices[m].position.y, vertices[m + 1].position.x - vertices[m].position.x, vertices[m + 2].position.y - vertices[m].position.y);
		if (boundingBox.intersects(playerBounds, overlap)) {
			eMap.deleteEnemy(m);	//FIX THIS
			break;
		}
	}
};

void Player::resolveCollision(sf::FloatRect collisionNormal, sf::FloatRect collided) {
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

sf::Vector2f Player::getPosition() {
	return hitbox.getGlobalBounds().getPosition();
}


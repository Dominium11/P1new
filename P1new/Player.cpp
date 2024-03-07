#include "Player.h"
#include <string>
#include <math.h>

using namespace sf;

Player::Player(std::string spritePath, int sizeX, int sizeY):
sizeY(sizeY), sizeX(sizeX)
{
	movementSpeed = 5;
	if (!texture.loadFromFile(spritePath))
	{
		throw std::invalid_argument("Missing file/Invalid path to Player sprite specified");
	}
	else {
		sprite.setTexture(texture);
	}
};

void Player::Update(sf::RenderWindow &window) {
	horizontal = 0;
	vertical = 0;
	if (Keyboard::isKeyPressed(Keyboard::A)) horizontal -= 1;
	if (Keyboard::isKeyPressed(Keyboard::D)) horizontal += 1;
	if (Keyboard::isKeyPressed(Keyboard::W)) vertical -= 1;
	if (Keyboard::isKeyPressed(Keyboard::S)) vertical += 1;

	if (horizontal != 0 && vertical != 0) {
		this->sprite.move(horizontal * movementSpeed * diagMod, vertical * movementSpeed * diagMod);
	}
	else {
		this->sprite.move(horizontal * movementSpeed, vertical * movementSpeed);
	}


};




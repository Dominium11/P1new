#include <SFML/Graphics.hpp>
#include "Wall.h"

#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_

class Player
{
	public:
		double movementSpeed;
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		Player(std::string spritePath, int sizeX, int sizeY, int posX, int posY);
		void Update(sf::RenderWindow &window ,std::vector<std::vector<Wall>>&walls);
	private:
		//Resolves collision with sf::Shape objects by taking current movement axis
		void resolveCollision(sf::FloatRect collisionNormal, sf::RectangleShape);
		sf::Texture texture;
		int sizeX, sizeY;
		bool moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
		short int horizontal = 0, vertical = 0;
		const double diagMod = 0.707106; ///Sin(45) to make angular movement match non-angular movement
};

#endif

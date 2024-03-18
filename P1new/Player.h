#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Level.h"

#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_

class Player
{
	public:
		double movementSpeed = 5;
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		Player(std::string spritePath, int sizeX, int sizeY, int posX, int posY, sf::Clock &clock);
		void Update(sf::RenderWindow& window, Level level);
	private:
		//Resolves collision with sf::Shape objects by taking current movement axis
		sf::Clock clock;
		void resolveCollision(sf::FloatRect collisionNormal, sf::RectangleShape);
		sf::Texture texture;
		int sizeX, sizeY;
		short int horizontal = 0, vertical = 0;
		const double diagMod = 0.707106; ///Sin(45) to make angular movement match non-angular movement
};

#endif

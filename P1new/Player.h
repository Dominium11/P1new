#include <SFML/Graphics.hpp>

#ifndef MY_HEADER_FILE_
#define MY_HEADER_FILE_

class Player
{
	public:
		float movementSpeed;
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		Player(std::string spritePath, int sizeX, int sizeY);
		void Update(sf::RenderWindow &window);
	private:
		sf::Texture texture;
		int sizeX, sizeY;
		bool moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
		short int horizontal = 0, vertical = 0;
		const float diagMod = 0.707106; ///Sin(45) to make angular movement match non-angular movement
};

#endif

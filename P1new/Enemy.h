#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Level.h"

#ifndef HEADER
#define HEADER

class Level;

class Enemy : public sf::Drawable{
public:
	double health = 100;
	double movementSpeed = 5;
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	Enemy(std::string spritePath, int sizeX, int sizeY, int posX, int posY, sf::Clock& clock);
	void Update(sf::RenderWindow& window, Level level);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Clock clock;
	//Resolves collision with sf::Shape objects by taking current movement axis
	void resolveCollision(sf::FloatRect collisionNormal, sf::RectangleShape);
	sf::Texture texture;
	int sizeX, sizeY;
	short int horizontal = 0, vertical = 0;
	double diagMod = 0.707106; ///Sin(45) to make angular movement match non-angular movement
};

#endif

#include "Wall.h"

Wall::Wall() {
	collider.setSize(sf::Vector2f(0, 0));
	collider.setPosition(sf::Vector2f(0, 0));
}

Wall::Wall(int width, int height, int top, int bottom, sf::Color color){
	collider.setSize(sf::Vector2f(width, height));
	collider.setFillColor(color);
	collider.setPosition(sf::Vector2f(top, bottom));
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states)const{
	target.draw(collider);
}
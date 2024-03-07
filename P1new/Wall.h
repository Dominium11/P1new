#pragma once
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable, sf::Transformable {
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		Wall();
		Wall(int width, int height, int top, int bottom, sf::Color color);
		void setPosition(int x, int y);
		sf::RectangleShape collider;
};


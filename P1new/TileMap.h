#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	sf::VertexArray getVertices();
	std::vector<int> getTileIds();
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	int width, height;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	std::vector<int> tileIds;
	sf::Texture m_tileset;
};




#include "TileMap.h"


TileMap::TileMap(int posX, int posY):posX(posX), posY(posY){}

bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];
            tileIds.push_back(tileNumber);

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x + posX, j * tileSize.y + posY);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x + posX, j * tileSize.y + posY);
            triangles[2].position = sf::Vector2f(i * tileSize.x + posX, (j + 1) * tileSize.y + posY);
            triangles[3].position = sf::Vector2f(i * tileSize.x + posX, (j + 1) * tileSize.y + posY);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x + posX, j * tileSize.y + posY);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x + posX, (j + 1) * tileSize.y + posY);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

sf::VertexArray TileMap::getVertices() {
    return this->m_vertices;
}

std::vector<int> TileMap::getTileIds() {
    return this->tileIds;
}
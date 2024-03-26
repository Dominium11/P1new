#include "Enemy.h"
#include <iostream>
EnemyMap::EnemyMap(){}

bool EnemyMap::pushNewEnemy(const std::string& tileset, sf::Vector2u tileSize, int tileNumber, int posX, int posY)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Triangles);
    m_vertices.resize(m_vertices.getVertexCount() + 6);

    // populate the vertex array, with two triangles per tile
    // find its position in the tileset texture
    int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
    int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

    // get a pointer to the triangles' vertices of the current tile
    sf::Vertex* triangles = &m_vertices[amountOfEnemies * 6];

    // define the 6 corners of the two triangles
    triangles[0].position = sf::Vector2f(posX, posY);
    triangles[1].position = sf::Vector2f(tileSize.x + posX, posY);
    triangles[2].position = sf::Vector2f(posX, tileSize.y + posY);
    triangles[3].position = sf::Vector2f(posX, tileSize.y + posY);
    triangles[4].position = sf::Vector2f(tileSize.x + posX, posY);
    triangles[5].position = sf::Vector2f(tileSize.x + posX, tileSize.y + posY);

    // define the 6 matching texture coordinates
    triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
    triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
    triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);

    amountOfEnemies += 1;

    return true;
}

sf::Vector2f EnemyMap::normalize(sf::Vector2f delta) {
    if (delta.x == 0.0 && delta.y == 0.0)
        return sf::Vector2f(0.0,0.0);

    return delta / std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

void EnemyMap::Update(sf::RenderWindow& window, sf::View playerView, Player player, TileMap map[]) {
    for (int i = 0; i < amountOfEnemies; i++) {
        sf::Vertex* triangles = &m_vertices[i * 6];
        sf::Vector2f delta = sf::Vector2f(player.getPosition().x - triangles[0].position.x, player.getPosition().y - triangles[0].position.y);
        float m = (player.getPosition().y - triangles[0].position.y) / (player.getPosition().x - triangles[0].position.x);
        std::cout << m << std::endl;
        for (int j = 0; j < 6; j++) {
            if (delta.x*delta.x+delta.y*delta.y < speed * speed)
            {
                // set to target if our speed would go beyond the target
                triangles[j].position.x = player.getPosition().x;
                triangles[j].position.y = player.getPosition().y;
            }
            else {
                triangles[j].position.x += speed * normalize(delta).x;
                triangles[j].position.y += speed * normalize(delta).y;
            }
        }
    }
}

void EnemyMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}

sf::VertexArray EnemyMap::getVertices() {
    return this->m_vertices;
}

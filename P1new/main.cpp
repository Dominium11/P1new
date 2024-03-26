#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "TileMap.h"
#include "Enemy.h"
#include <fstream>
#include <iostream>
#include <random>
using namespace sf;

/// <summary>
/// Implement more color templates
/// </summary>
struct Colors{

};
/*
unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width, height;
    memcpy(&width, info + 18, sizeof(int));
    memcpy(&height, info + 22, sizeof(int));

    int heightSign = 1;
    if (height < 0) {
        heightSign = -1;
    }

    int size = 3 * width * abs(height);
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    if (heightSign == 1) {
        for (i = 0; i < size; i += 3)
        {
            // flip the order of every 3 bytes
            unsigned char tmp = data[i];
            data[i] = data[i + 2];
            data[i + 2] = tmp;
        }
    }
    return data;
}
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "pp-projekt-gra");
    window.setFramerateLimit(144);

    std::ifstream MyFile("Level1.map"); // Top left level
    Clock clock;
    Player player("./Sprites/player.jpg", 100, 100, 700, 700, clock);
    sf::View playerView;

    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 19); // amount of levels

    // define the level with an array of tile indices
    std::vector<int> level;

    int levelSize = 2;
    const int sizeOfMap = 36;
    TileMap maps[sizeOfMap];
    EnemyMap eMap;
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 0, 0);
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 64, 64);
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 128, 128);
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 128*2, 128*2);
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 128, 128);
    eMap.pushNewEnemy("./Sprites/tileset.png", sf::Vector2u(64, 64), 2, 128, 128);
    for (int i = 0; i < sizeOfMap; i++) {
        for (int mapHeight = 0; mapHeight < 8 * levelSize; mapHeight++) 
        {
            for (int mapWidth = 0; mapWidth < 8 * levelSize; mapWidth++) {
                MyFile.close();
                if (dist6(rng) == 0) {
                    level.push_back(0); //Nothing
                }
                else if (dist6(rng) == 1) {
                    level.push_back(1); //Enemy spawner
                }
                else {
                    level.push_back(1); //Wall
                }
            }
        }
        TileMap x(1024 * (i % 6), 1024 * (i / 6));
        if (!x.load("./Sprites/tileset.png", sf::Vector2u(64, 64), level, 8 * levelSize, 8 * levelSize))
            return -1;
        maps[i] = x;

        level.clear();
    }

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        playerView.reset(sf::FloatRect(player.hitbox.getPosition().x - 512.f, player.hitbox.getPosition().y - 512.f, 1024.f, 1024.f));
        playerView.zoom(1.5f);
        playerView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        sf::Vector2f viewCenter(playerView.getCenter());
        sf::Vector2f viewSize(playerView.getSize());
        sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);

        player.Update(window, maps, playerView);
        eMap.Update(window, playerView, player, maps);
        //for (Enemy enemy : level.enemies) {
        //    enemy.Update(window, level);
        //}

        window.setView(playerView);

        window.clear();

        /*
        for (Enemy enemy : level.enemies) {
            auto rect = enemy.hitbox.getGlobalBounds();
            if (rect.intersects(currentViewRect)) {
                window.draw(enemy);
            }
        }*/
        for (int i = 0; i < sizeOfMap; i++) {
            sf::FloatRect boundingBox(maps[i].getPosition().x, maps[i].getPosition().y, maps[i].width, maps[i].height);
            if (boundingBox.intersects(playerView.getViewport())) {
                window.draw(maps[i]);
            }
        }
        window.draw(eMap);
        window.draw(player.sprite);
        window.display();

        Time elapsed = clock.restart();
    }

    return 0;
}
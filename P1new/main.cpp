#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Level.h"
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
    sf::RenderWindow window(sf::VideoMode(1900, 1100), "pp-projekt-gra");
    window.setFramerateLimit(144);

    std::ifstream MyFile("Level1.map");
    Clock clock;
    Player player("./Sprites/player.jpg", 100, 100, 700, 700, clock);

    std::random_device rand;
    std::mt19937 rng(rand());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 2); // distribution in range [1, 6]
    for (int am = 0; am < 2; am ++) {
        for (int i = 0; i < 2 * 3; i++) {
            for (int j = 0; j < 2 * 3; j++) {
                std::cout << j;
            }
            std::cout << std::endl;
        }
    }

    int levelWidth = 38;
    int levelHeight = 22;
    Level level;
    std::string levelTemplate;
    int mapSize = 5;
    for (int mapHeight = -mapSize; mapHeight < mapSize; mapHeight++) {
        for (int mapWidth = -mapSize; mapWidth < mapSize; mapWidth++) {
            for (int i = 0; i < levelHeight; i++) {
                std::getline(MyFile, levelTemplate);
                for (int j = 0; j < levelWidth; j++) {
                    if (levelTemplate[j] == '#') {
                        Wall newWall(50, 50, 50 * j + 1900 * mapWidth, 50 * i + 1100 * mapHeight, sf::Color::Red);
                        level.walls.push_back(newWall);
                    }
                    else if (levelTemplate[j] == 'E') {
                        Enemy newEnemy("./Sprites/enemy.jpg", 100, 100, 50 * j + 1900 * mapWidth, 50 * i + 1100 * mapHeight, clock);
                        level.enemies.push_back(newEnemy);
                    }
                }
            }
            MyFile.close();
            switch (dist6(rng)) {
            case 1:
                MyFile.open("Level2.map");
                break;
            case 2:
                MyFile.open("Level1.map");
                break;
            }
        }
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

        sf::View playerView(sf::FloatRect(player.hitbox.getPosition().x - 950.f, player.hitbox.getPosition().y - 550.f, 1900.f, 1100.f));
        playerView.zoom(1.5f);
        playerView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

        player.Update(window, level);
        for (Enemy enemy : level.enemies) {
            enemy.Update(window, level);
        }

        window.setView(playerView);

        window.clear();
        for (Wall wall : level.walls) {
            window.draw(wall);
        }
        for (Enemy enemy : level.enemies) {
            window.draw(enemy);
        }
        window.draw(player.sprite);
        window.display();

        Time elapsed = clock.restart();
    }

    return 0;
}
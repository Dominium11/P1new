#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Level.h"
#include <fstream>
#include <iostream>
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

    int levelWidth = 38;
    int levelHeight = 22;
    Level level(levelWidth, levelHeight);
    std::string levelTemplate;
    for(int i = 0; i < levelHeight; i++){
        std::getline(MyFile, levelTemplate);
        for (int j = 0; j < levelWidth; j++) {
            if (levelTemplate[j] == '.') {
                Wall newWall;
                level.walls[j][i] = newWall;
            }
            else if (levelTemplate[j] == '#') {
                Wall newWall(50, 50, 50 * j, 50*i, sf::Color::Red);
                level.walls[j][i] = newWall;
            }
            else if (levelTemplate[j] == 'E') {
                Enemy newEnemy("./Sprites/enemy.jpg", 100, 100, 50 * j, 50 * i, clock);
                level.enemies.push_back(newEnemy);
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
        player.Update(window, level);
        for (unsigned int i = 0; i < level.enemies.size(); i++) {
            level.enemies[i].Update(window, level);
            std::cout << level.enemies[i].sprite.getPosition().y << std::endl;
        }

        window.clear();
        for (std::vector row : level.walls) {
            for (Wall wall : row) {
                window.draw(wall);
            }
        }
        for (unsigned int i = 0; i < level.enemies.size(); i++) {
            window.draw(level.enemies[i]);
        }
        window.draw(player.sprite);
        window.display();

        Time elapsed = clock.restart();
    }

    return 0;
}
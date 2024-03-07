#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Level.h"
#include <fstream>

using namespace sf;

/// <summary>
/// Implement more color templates
/// </summary>
struct Colors{

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "pp-projekt-gra");
    window.setFramerateLimit(144);

    std::ifstream MyFile("Level1.map");

    int levelWidth = 39;
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
        }
    }

    Player player("./Sprites/player.jpg", 100, 100, 700, 700);
    Clock clock;
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

        player.Update(window, level.walls);
        window.clear();
        for (std::vector row : level.walls) {
            for (Wall wall : row) {
                window.draw(wall);
            }
        }
        window.draw(player.sprite);
        window.display();
        Time elapsed = clock.restart();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "pp-projekt-gra");
    window.setFramerateLimit(144);

    Player player("./Sprites/player.jpg", 100, 100);
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

        player.Update(window);

        window.clear();
        window.draw(player.sprite);
        window.display();
        Time elapsed = clock.restart();
    }

    return 0;
}
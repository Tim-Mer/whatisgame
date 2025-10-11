#include "config.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);

    
    sf::Text text(GAME_FONT, "Hello world!", 50);

    sf::CircleShape c1(10.f);
    c1.setFillColor(sf::Color(100, 250, 50));

    constexpr std::array level = {
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
    };

    TileMap map;
    if (!map.load("tileset.png", {32, 32}, level.data(), 10, 10))
        return -1;


    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        //window.draw(text);
        window.draw(map);
        window.draw(c1);
        c1.move({1.f, 1.f});
        
        window.display();
    }
}

#include "config.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);

    
    sf::Text text(GAME_FONT, "Hello world!", 50);

    sf::Texture texture("res/Terrain/Water_Background_color.png", false, sf::IntRect({0, 0}, {64, 64}));
    sf::Sprite sprite(texture);
    //sprite.setTextureRect(sf::IntRect({100, 100}, {64, 64}));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.draw(sprite);
        window.display();
    }
}

#include "config.hpp"
#include "graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);

    
    sf::Text text(GAME_FONT, "Hello world!", 50);

    Balls ball;
    ball.load(WINDOW_WIDTH/10, WINDOW_HEIGHT/10);
    
    GridMap grid;
    grid.load(WINDOW_WIDTH/10, WINDOW_HEIGHT/10);

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        //window.draw(text);
        
        window.draw(grid);
        window.draw(c1);
        c1.move({1.f, 1.f});
        
        window.display();
    }
}

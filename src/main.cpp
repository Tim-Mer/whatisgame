#include "config.hpp"
#include "funcs.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);

    
    sf::Text text(GAME_FONT, "Hello world!", 50);

    //Balls ball;
    //ball.load({0.f, 0.f}, {WINDOW_WIDTH-1.f, WINDOW_HEIGHT-1.f});

    GridMap grid;
    grid.load(WINDOW_WIDTH/10, WINDOW_HEIGHT/10);

    //Paddles paddle;
    //paddle.load();

    Player p1, p2;
    p1.load({1.f, 1.f}, PURPLE, {1.f, -1.f});
    p2.load({WINDOW_WIDTH - 8.f, 1.f}, ORANGE, {-1.f, -1.f});

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }
// CLEAR
        window.clear();
// DRAW     
        window.draw(grid);
        window.draw(p1);
        window.draw(p2);
// MOVE        
        p1.move();
        p2.move();
// DISPLAY        
        window.display();
    }
}

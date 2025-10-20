#include "config.hpp"
#include "funcs.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);
    
    //sf::Text text(GAME_FONT, "Hello world!", 50);

    //GridMap grid;
    //grid.load(WINDOW_WIDTH/10, WINDOW_HEIGHT/10);
// Adding players
    std::vector<Player*> players;
    Player *p;
    p = new Player({1.f, 1.f}, PURPLE, {1.f, -1.f});
    players.push_back(p);
    p = new Player({WINDOW_WIDTH - 8.f, 1.f}, ORANGE, {-1.f, -1.f});
    players.push_back(p);

    std::cout << "Num Players: " << players.size() << std::endl;

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
        window.draw(grid);
        for (size_t i=0; i<players.size(); i++) {
//DRAW
            window.draw(*players[i]);
//COLLIDE
            players[i]->collide(grid);
//MOVE
            players[i]->move();
        }
// DISPLAY
        window.display();
    }
    for (size_t i=0; i<players.size(); i++) {
        delete players[i];
    }
    return EXIT_SUCCESS;
}

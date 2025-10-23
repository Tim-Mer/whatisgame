#include "config.hpp"
#include "funcs.hpp"

int main()
{
//GAME SETTINGS
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 2;
//WINDOW CREATION
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed, settings);
    window.setFramerateLimit(60);
    
//PLAYERS
    std::vector<Player*> players;
    Player *p;
    sf::RectangleShape player_area({WINDOW_WIDTH/20, WINDOW_HEIGHT/10});
    p = new Player(player_area, PURPLE, ORANGE, {0.f, 0.f}, false);
    players.push_back(p);
    p = new Player(player_area, ORANGE, PURPLE, {(float) WINDOW_WIDTH/20, 0.f}, true);
    players.push_back(p);
    p = NULL;

    std::cout << "Num Players: " << players.size() << std::endl;

//MAIN LOOP
    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }
//CLEAR
        window.clear();

        for (size_t i=0; i<players.size(); i++) {
//DRAW
            window.draw(*players[i]);
//COLLIDE
            players[i]->collide();
//MOVE
            players[i]->move();
        }
//DISPLAY
        window.display();
    }
//DESYTOY PLAYER OBJ
    for (size_t i=0; i<players.size(); i++) {
        delete players[i];
    }
    return EXIT_SUCCESS;
}

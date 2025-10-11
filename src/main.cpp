#include "config.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), WINDOW_NAME, sf::State::Windowed);
    window.setFramerateLimit(120);

    
    sf::Text text(GAME_FONT, "Hello world!", 50);

    sf::CircleShape c1(4.f);
    c1.setFillColor(PURPLE);
    c1.setOutlineThickness(1.f);
    c1.setOutlineColor(BLACK);

    std::vector<std::vector<sf::RectangleShape>> boxes;

    int counter = 0;
    for(size_t i=0; i<72; i++) {
        std::vector<sf::RectangleShape> row;
        for(size_t j=0; j<72; j++) {
            sf::RectangleShape cb({10.f, 10.f});
            if(j>36){
                cb.setFillColor(PURPLE);
            } else {
                cb.setFillColor(ORANGE);
            }
            cb.setPosition({(float)j*10, (float)i*10});
            if (ENABLE_GRID) {
                cb.setOutlineThickness(1.f);
                cb.setOutlineColor(BLACK);
            }
            row.push_back(cb);
        }
        boxes.push_back(row);
    }

    while(window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        //window.draw(text);
        
        for(size_t i=0; i<boxes.size(); i++) {
            for(size_t j=0; j<boxes[i].size(); j++) {
                window.draw(boxes[i][j]);
            }
        }
        window.draw(c1);
        c1.move({1.f, 1.f});
        
        window.display();
    }
}

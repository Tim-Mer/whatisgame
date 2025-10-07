#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1280, 720}), "CMake SFML Project");
    window.setFramerateLimit(120);

    const sf::Font font("resources/Gidole-Regular.ttf");
    sf::Text text(font, "Hello SFML", 50);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}

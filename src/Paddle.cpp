#include <classes.hpp>

void Paddle::load(sf::Vector2f start_pos, sf::Color player_colour) {
/*
    start_pos: The starting position of the players paddle
    player_colour: Players colour
*/
    paddle.setSize({5.f, 30.f});
    paddle.setFillColor(player_colour);
    paddle.setPosition(start_pos);
}

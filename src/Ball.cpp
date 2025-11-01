#include <classes.hpp>

void Ball::load(sf::Vector2f start_pos, sf::Color player_colour, sf::Vector2f init_vel) {
/*
    start_pos: The start position of the ball
    player_colour: Players Colour
    init_vel: The initial velocity of the players ball
*/
    p_ball.setFillColor(player_colour);
    p_ball.setRadius(4.f);
    p_ball.setOutlineThickness(1.f);
    p_ball.setOutlineColor(BLACK);
    p_ball.setPosition(start_pos);
    vel = init_vel;
}

void Ball::move() {
    // Set speed limit
    p_ball.move(vel);
    //std::cout << "vel: " << vel.x << ", " << vel.y << std::endl;
}

void Ball::bounce(sf::Vector2f dir) {
/*
    dir x/y value must be either 1 or -1
    up/down:    {1, -1}
    left/right: {-1, 1}
*/
    vel.x *= dir.x;
    vel.y *= dir.y;
}

sf::Vector2f Ball::get_vector() {
    return vel;
}

sf::CircleShape Ball::get_ball() {
    return p_ball;
}
#include "funcs.hpp"

void GridMap::load(int width, int height) {
    //Load Box
    box.setSize({(float) width, (float) height});
    //Load grid
    for (size_t i=0; i<height; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=0; j<width; j++) {
                sf::RectangleShape cb({10.f, 10.f});
                if (j>(width/2)-1) {
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
}

bool GridMap::edge_collision(sf::CircleShape ball) {
    return box.getLocalBounds().contains(ball.getPosition());
}

void Ball::load(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel) {
    p_ball.setFillColor(pl_col);
    p_ball.setRadius(4.f);
    p_ball.setOutlineThickness(1.f);
    p_ball.setOutlineColor(BLACK);
    p_ball.setPosition(start_pos);
    p_ball.move(init_vel);
}

void Ball::move(sf::Vector2f vec) {
    vel+=vec;
    // Set speed limit
    if ( abs(vel.x) > MAX_SPEED || abs(vel.y) > MAX_SPEED) {
        vel = vel.normalized();
    }
    p_ball.move(vel);
}

sf::Vector2f Ball::get_vector() {
    return vel;
}

sf::CircleShape Ball::get_ball() {
    return p_ball;
}

void Paddle::load(sf::Vector2f start_pos, sf::Color pl_col) {
    paddle.setSize({5.f, 30.f});
    paddle.setFillColor(pl_col);
    paddle.setPosition(start_pos);
}

Player::Player(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel){
    p_paddle.load(start_pos, pl_col);
    p_ball.load(start_pos, pl_col, init_vel);
}

void Player::move() {
    //p_ball.move({1.f, 1.f});
}

void Player::collide(GridMap map) {
    if (map.edge_collision(p_ball.get_ball())) {
        p_ball.move({-1.f, -1.f});
    }
    p_ball.move({1.f, 1.f});
}
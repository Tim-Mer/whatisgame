#include "funcs.hpp"

void GridMap::load(sf::RectangleShape in_box, sf::Color p_col, sf::Vector2f start_point) {
    int x = in_box.getSize().x + start_point.x;
    int y = in_box.getSize().y + start_point.y;
    //Load grid
    for (size_t i=start_point.y; i<y; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=start_point.x; j<x; j++) {
                sf::RectangleShape cb({10.f, 10.f});
                cb.setFillColor(p_col);
                cb.setPosition({(float) j*10, (float) i*10});
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
    //return box.getLocalBounds().contains(ball.getPosition()); 
    return false;
}

void Ball::load(sf::Vector2f start_pos, sf::Color player_colour, sf::Vector2f init_vel) {
    p_ball.setFillColor(player_colour);
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

void Paddle::load(sf::Vector2f start_pos, sf::Color player_colour) {
    paddle.setSize({5.f, 30.f});
    paddle.setFillColor(player_colour);
    paddle.setPosition(start_pos);
}

Player::Player(sf::RectangleShape player_area, sf::Color player_colour, sf::Color grid_colour, sf::Vector2f top_corner, bool player_right) {
    /*
    player area: Total area that is in the players control including further expanded area
    player_colour: Player colour
    corner: The top left corner of the players area
    player_right: True for paddle and ball starting on the right, false for left
    
    - Need to calculate and send the starting position for both paddles
    - Calculate the initial velocity of each ball (Maybe randomly towards the middle or close enough)
    - Send the entire player area to the p_grid to let it load the grid
    */

    float player_centre = player_area.getSize().y/2;
    sf::Vector2f paddle_start({1.f, player_centre});
    if (player_right) {
        paddle_start.x = WINDOW_WIDTH - 8.f;
    }
    p_grid.load(player_area, grid_colour, top_corner);
    p_paddle.load(paddle_start, player_colour);
    //p_ball.load(ball_start, player_colour, ball_velocity);
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
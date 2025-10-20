#include "funcs.hpp"

void GridMap::load(sf::RectangleShape in_box, sf::Color p_col, sf::Vertex start_point) {
    //Load Box
    box = in_box;
    int x = box.getSize().x + start_point.position.x;
    int y = box.getSize().y + start_point.position.y;
    //box.setSize({(float) width, (float) height});
    //Load grid
    for (size_t i=start_point.position.y; i<y; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=start_point.position.x; j<x; j++) {
                sf::RectangleShape cb({10.f, 10.f});
                cb.setFillColor(p_col);
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

Player::Player(sf::RectangleShape player_area, sf::Color pl_col, sf::Vertex corner, bool tright_fleft) {
    /*
    player area: Total area that is in the players control including further expanded area
    pl_col: Player colour
    corner: The top left corner of the players area
    tright_fleft: True for paddle and ball starting on the right, false for left
    
    - Need to calculate and send the starting position for both paddles
    - Calculate the initial velocity of each ball (Maybe randomly towards the middle or close enough)
    - Send the entire player area to the p_grid to let it load the grid
    */
    p_paddle.load(start_pos, pl_col);
    p_ball.load(start_pos, pl_col, init_vel);
    p_grid.load((sf::RectangleShape) start_pos, pl_col, start_pos);
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
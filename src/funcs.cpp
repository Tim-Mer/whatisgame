#include "funcs.hpp"

void GridMap::load(sf::RectangleShape in_box, sf::Color p_col, sf::Vector2f start_point) {
/*
    in_box: The bounds of the players area
    p_col: Players Colour
    start_point: The top left corner of the players area
*/
//Setting player_area
    player_area.setPointCount(4);
    player_area.setPoint(0, in_box.getPoint(0).componentWiseMul({10, 10}));
    player_area.setPoint(1, in_box.getPoint(1).componentWiseMul({10, 10}));
    player_area.setPoint(2, in_box.getPoint(2).componentWiseMul({10, 10}));
    player_area.setPoint(3, in_box.getPoint(3).componentWiseMul({10, 10}));
    player_area.setOutlineColor(BLACK);
    player_area.setFillColor(sf::Color::Transparent);
    player_area.setOutlineThickness(1.f);

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

int GridMap::getNumBoxes() {
    return (int) boxes.size() + boxes[1].size();
}

sf::ConvexShape GridMap::getPlayerArea() {
    return player_area;
}

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
/*
    start_pos: The starting position of the players paddle
    player_colour: Players colour
*/
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
*/
//GRID
    p_grid.load(player_area, grid_colour, top_corner);
//PADDLE
    float player_centre = ((player_area.getSize().y*10)/2)-15;
    sf::Vector2f paddle_start({((player_right) ? WINDOW_WIDTH - 12.f : 5.f), player_centre});
    p_paddle.load(paddle_start, player_colour);
//BALL
    sf::Vector2f ball_start = {
        (top_corner.x*10)+((player_area.getSize().x*10)*((player_right) ? (float) 0.25 : (float) 0.75)),
        (top_corner.y*10)+((player_area.getSize().y*10)/2)
    };
    sf::Vector2f ball_velocity = {-1.f, 0.f};
    p_ball.load(ball_start, player_colour, ball_velocity);
//SCORE
    score = p_grid.getNumBoxes();
}

void Player::move() {
    p_ball.move({1.f, 1.f});
}

void Player::collide() {
    sf::CircleShape ball = p_ball.get_ball();
    //sf::RectangleShape area = p_grid;
}

//sf::Text Player::getScore() {
    
//}
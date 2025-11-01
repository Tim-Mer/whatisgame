#include "funcs.hpp"

void GridMap::load(sf::RectangleShape in_box, sf::Color p_col, sf::Vector2f start_point, bool player_right) {
/*
    in_box: The bounds of the players area
    p_col: Players Colour
    start_point: The top left corner of the players area
*/
    p_right = player_right;
    box_colour = p_col;
//Setting player_area
/*
p1    p0 p0     p1
+-------+-------+
|       |       |
|       |       |
|       |       |
|       |       |
|       |       |
+-------+-------+
p2    p3 p3     p2

Written this way so that when adding a point to the convex shape it is appended to the end of the list.
Also means that walls from p0-p1, p1-p2 and p2-p3 are stable and never change. It is only between p3-p0
*/
    player_area.setPointCount(4);
    //Top Left
    player_area.setPoint(0, in_box.getPoint((player_right) ? 0 : 1).componentWiseMul({10, 10})+start_point);
    //Top Right
    player_area.setPoint(1, in_box.getPoint((player_right) ? 1 : 0).componentWiseMul({10, 10})+start_point);
    //Bottom Right
    player_area.setPoint(2, in_box.getPoint((player_right) ? 2 : 3).componentWiseMul({10, 10})+start_point);
    //Bottom Left
    player_area.setPoint(3, in_box.getPoint((player_right) ? 3 : 2).componentWiseMul({10, 10})+start_point);
    player_area.setOutlineColor(BLACK);
    player_area.setFillColor(sf::Color::Transparent);
    player_area.setOutlineThickness(1.f);

    size_t num_boxes_across = player_area.getPoint((player_right) ? 1 : 0).x/10;
    size_t num_boxes_down = player_area.getPoint(2).y/10;
//Load grid
    for (size_t i=start_point.y; i<num_boxes_down; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=start_point.x/10; j<num_boxes_across; j++) {
                sf::RectangleShape cb({10.f, 10.f});
                cb.setFillColor(p_col);
                cb.setPosition({(float) j*10, (float) i*10});
                if (ENABLE_GRID) {
                    cb.setOutlineThickness(1.f);
                    cb.setOutlineColor(BLACK);
                }
                row.push_back(cb);
            }
            if (player_right) {
                std::reverse(row.begin(), row.end());
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

bool GridMap::hitTopBottom(sf::CircleShape ball) {
    sf::Vector2f point = ball.getPosition();
    sf::Vector2f p1 = player_area.getPoint(0), p2 = player_area.getPoint(3);
    return (point.y < p1.y || point.y > p2.y);
}

bool GridMap::hitHomeEdge(sf::CircleShape ball) {
    sf::Vector2f point = ball.getPosition();
    sf::Vector2f p1 = player_area.getPoint(1);
    if (p_right) {
        return (point.x > p1.x);
    }
    return (point.x < p1.x);
}

sf::ConvexShape GridMap::getPlayerArea() {
    return player_area;
}

std::vector<sf::RectangleShape> GridMap::getBorderBoxes(bool p_right) {
    std::vector<sf::RectangleShape> tmp;
    size_t which_box = (p_right) ? boxes[0].size()-1 : 0;
    for (size_t i=0; i<boxes.size(); i++) {
        tmp.push_back(boxes[i][which_box]);
    }
    return tmp;
}

sf::RectangleShape GridMap::removeBox(size_t y_location) {
/*
    Removes a box from the grid and returns said box
*/
    sf::RectangleShape tmp = boxes[y_location].back();
    boxes[y_location].pop_back();
    return tmp;
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

void Paddle::load(sf::Vector2f start_pos, sf::Color player_colour) {
/*
    start_pos: The starting position of the players paddle
    player_colour: Players colour
*/
    paddle.setSize({5.f, 30.f});
    paddle.setFillColor(player_colour);
    paddle.setPosition(start_pos);
}

Player::Player(sf::RectangleShape player_area, sf::Color player_colour, sf::Color grid_colour, sf::Vector2f top_corner, bool player_right, char* name) {
/*
    player area: Total area that is in the players control including further expanded area
    player_colour: Player colour
    corner: The top left corner of the players area
    player_right: True for paddle and ball starting on the right, false for left
*/
//GRID
    p_grid.load(player_area, grid_colour, top_corner, player_right);
//PADDLE
    float player_centre = ((player_area.getSize().y*10)/2)-15;
    sf::Vector2f paddle_start({((player_right) ? WINDOW_WIDTH - 12.f : 5.f), player_centre});
    p_paddle.load(paddle_start, player_colour);
//BALL
    sf::Vector2f ball_start = {
        (top_corner.x)+(10*(player_area.getSize().x)*((player_right) ? (float) 0.25 : (float) 0.75)),
        (top_corner.y)+(10*(player_area.getSize().y)/2)
    };
    sf::Vector2f ball_velocity = {-2.f, -2.f};
    if (player_right) {ball_velocity = {2.f, 2.f};}
    p_ball.load(ball_start, player_colour, ball_velocity);
//SCORE
    score = p_grid.getNumBoxes();
    p_name = name;
//OTHER
    p_right = player_right;
}

void Player::move() {
    p_ball.move();
}

void Player::detectCollision() {
/*
p1    p0 p0     p1
+-------+-------+
|       |       |
|       |       |
|       |       |
|       |       |
|       |       |
+-------+-------+
p2    p3 p3     p2

for both,
if ball is near the line p0/p1 it needs to bounce back downwards
if the ball is on or very near the line p1/p2 it needs to bounce back in the x direction of p0
if the ball is near the line p2/p3 it needs to bounce upwards


could check total bounds periodiocally to reset the ball if it is outside the playable area
how to check if a ball is within a square 
how to check if a point is within a convex shape
*/

    if (p_grid.hitTopBottom(p_ball.get_ball())) {
        p_ball.bounce({1.f, -1.f});
        std::cout << p_name << " Hit top/bottom" << std::endl;
    } else if (p_grid.hitHomeEdge(p_ball.get_ball())) {
        p_ball.bounce({-1.f, 1.f});
        std::cout << p_name << " Hit Home" << std::endl;
    }

}

/*sf::Text Player::getScore() {
    Returns a printable score for the player
}*/
#include "classes.hpp"

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

void Player::detectCollision(Player *opponent) {
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
    sf::CircleShape c_ball = p_ball.get_ball();
    //check if ball is outside the player area
    if (p_grid.getPlayerArea().getGlobalBounds().contains(c_ball.getPosition())) {return;}
    
    //check where the ball left the field
    if (p_grid.hitTopBottom(c_ball)) {
        p_ball.bounce({1.f, -1.f});
        std::cout << p_name << " Hit top/bottom" << std::endl;
    } else if (p_grid.hitHomeEdge(c_ball)) {
        p_ball.bounce({-1.f, 1.f});
        std::cout << p_name << " Hit Home" << std::endl;
    } else {
        //check where it has breached the opponents boxes
        std::vector<sf::RectangleShape> op_boxes = opponent->getEdgeBoxes();
        sf::Vector2f ball_point = c_ball.getPosition();
        for (size_t i=0; i<op_boxes.size(); i++) {
            if (op_boxes[i].getGlobalBounds().contains(ball_point)) {
                p_ball.bounce({-1.f, 1.f});
                std::cout << p_name << " Hit Box: " << i << std::endl;
            }
        }
    }
    return;
}

std::vector<sf::RectangleShape> Player::getEdgeBoxes() {
    return p_grid.getBorderBoxes(p_right);
}

/*sf::Text Player::getScore() {
    Returns a printable score for the player
}*/
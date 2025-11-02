#include <classes.hpp>

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
    float x=0, y=0;
//Load grid
    for (size_t i=0; i<num_boxes_down; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=0; j<num_boxes_across; j++) {
                x = start_point.x+(j*10);
                y = i*10;
                sf::RectangleShape cb({10.f, 10.f});
                cb.setFillColor(p_col);
                cb.setPosition({x, y});
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

int GridMap::getNumBoxes() {
    return (int) boxes.size() + boxes[1].size();
}

bool GridMap::hitTopBottom(sf::CircleShape ball) {
    sf::Vector2f point = ball.getPosition();
    sf::Vector2f p1 = player_area.getPoint(0), p2 = player_area.getPoint(3);
    return (point.y < p1.y || point.y > p2.y);
}

bool GridMap::hitHomeEdge(sf::CircleShape ball) {
    // Instead of bouncing the ball is reset with a time penalty?
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
    size_t which_box = 0;
    for (size_t i=0; i<boxes.size(); i++) {
        which_box = boxes[i].size()-1;
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
    //Need to redefine the player_area before returning
    return tmp;
}

void GridMap::addBox(sf::RectangleShape box, size_t y_location) {
    box.setFillColor(box_colour);
    boxes[y_location].push_back(box);
    //Need to redefine the player_area before returning
}

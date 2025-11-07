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
p0    p1 p1     p0
+-------+-------+
|       |       |
|       |       |
|       |       |
|       |       |
|       |       |
+-------+-------+
p3    p2 p2     p3

Written this way so that when adding a point to the convex shape it is appended to the end of the list.
Also means that walls from p0-p1, p1-p2 and p2-p3 are stable and never change. It is only between p3-p0
*/
    player_area.setPointCount(4);
    //Top Left
    player_area.setPoint(0, in_box.getPoint((player_right) ? 1 : 0).componentWiseMul({10, 10})+start_point);
    //Top Right
    player_area.setPoint(1, in_box.getPoint((player_right) ? 0 : 1).componentWiseMul({10, 10})+start_point);
    //Bottom Right
    player_area.setPoint(2, in_box.getPoint((player_right) ? 3 : 2).componentWiseMul({10, 10})+start_point);
    //Bottom Left
    player_area.setPoint(3, in_box.getPoint((player_right) ? 2 : 3).componentWiseMul({10, 10})+start_point);
    player_area.setOutlineColor(BLACK);
    player_area.setFillColor(sf::Color::Transparent);
    player_area.setOutlineThickness(1.f);

    
    size_t num_boxes_across = player_area.getPoint((player_right) ? 0 : 1).x/BOX_SIZE;
    size_t num_boxes_down = player_area.getPoint(2).y/BOX_SIZE;
    float x=0, y=0;
//Load grid
    for (size_t i=0; i<num_boxes_down; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=0; j<num_boxes_across; j++) {
                x = start_point.x+(j*BOX_SIZE);
                y = i*BOX_SIZE;
                sf::RectangleShape cb({BOX_SIZE, BOX_SIZE});
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
    sf::Vector2f p1 = player_area.getPoint(0), p2 = player_area.getPoint(player_area.getPointCount()-1);
    return (point.y < p1.y || point.y > p2.y);
}

bool GridMap::hitHomeEdge(sf::CircleShape ball) {
    // Instead of bouncing the ball is reset with a time penalty?
    sf::Vector2f point = ball.getPosition();
    sf::Vector2f p1 = player_area.getPoint(0);
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
    reconstructPlayerArea();
    return tmp;
}

void GridMap::addBox(sf::RectangleShape box, size_t y_location) {
    box.setFillColor(box_colour);
    boxes[y_location].push_back(box);
    //Need to redefine the player_area before returning
    reconstructPlayerArea();
}

void GridMap::reconstructPlayerArea() {
/*
This function will reconstruct the player_area ConvexShape to be use for initial collision detection

sfml box point locations for RectangleShape
0-----1
|     |
|     |
3-----2
*/
    std::vector<sf::RectangleShape> edge_boxes = getBorderBoxes(p_right);
    std::vector<sf::Vector2f> new_points;
    if (!p_right) {
        //add wiggle
        for (size_t i=0; i<edge_boxes.size(); i++) {
            edge_boxes[i].move({BOX_SIZE, 0});
        }
    }
    player_area.setPoint(1, edge_boxes[0].getPosition());
    float cur_x = player_area.getPoint(1).x;
    for (size_t i=1; i<edge_boxes.size(); i++) {
        if (edge_boxes[i].getPosition().x != cur_x) {
            new_points.push_back({cur_x, edge_boxes[i].getPosition().y});
            new_points.push_back(edge_boxes[i].getPosition());
            cur_x = edge_boxes[i].getPosition().x;
        }
    }



    if (new_points.size()>0) {
        player_area.setPointCount(4+new_points.size());
        //need to add new boxes
        for (size_t i=0; i<new_points.size(); i++) {
            player_area.setPoint(2+i, new_points[i]);
        }
    }


    //Set last point to the bottom corner of the first box in the last row of boxes
    player_area.setPoint(player_area.getPointCount()-1, {player_area.getPoint(0).x, edge_boxes.back().getPosition().y+BOX_SIZE});
    // Set the second last point to have the cur_x as x and the y value of the last point
    player_area.setPoint(player_area.getPointCount()-2, {cur_x, player_area.getPoint(player_area.getPointCount()-1).y});




/*
    std::vector<sf::Vector2f> new_points;
    size_t which_top_point = (p_right) ? 0 : 1;
    size_t which_bottom_point = (p_right) ? 3 : 2;
    size_t which_last_point = (p_right) ? 2 : 3;
    //starting at point(1) of player_area, need to count the number of squares down 
    //that are different from the starting x value of point(1)

    //from p1 to the second last point see if anything needs to be changed
    player_area.setPoint(1, boxes[0].back().getPosition());
    float cur_x = player_area.getPoint(1).x;
    for (size_t i=1; i<boxes.size(); i++) {
        //check if the current box is at the same x as the cur_x
        if ( boxes[i].back().getPoint(which_top_point).x != cur_x) {
            new_points.push_back(boxes[i-1].back().getPoint(which_bottom_point));
            new_points.push_back(boxes[i].back().getPoint(which_top_point));
            cur_x = boxes[i].back().getPoint(which_top_point).x;
        }
        //if it is nothing needs to be done and no new point needs to be added
        //if it is different then need to add a point as the bottom of the previous box and the top of the current box
    }
    //at the end the last point needs to be updated to the cur_x for its x coord
    player_area.setPointCount(4+new_points.size());
    
    //TODO: Add all the points from the new_points vector
    //-------------HERE!!!!------------
    if (new_points.size()>0) {
        for (size_t i=0; i<new_points.size(); i++) {
            player_area.setPoint(i+2, new_points[i]);
        }
    }

    //Set last point to the bottom corner of the first box in the last row of boxes
    player_area.setPoint(player_area.getPointCount()-1, boxes.back()[0].getPoint(which_last_point));
    // Set the second last point to have the cur_x as x and the y value of the last point
    player_area.setPoint(player_area.getPointCount()-2, {cur_x, player_area.getPoint(player_area.getPointCount()-1).y});*/
}

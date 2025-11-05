#pragma once
#include "config.hpp"

class GridMap : public sf::Drawable {
public:
    void load(sf::RectangleShape in_box, sf::Color p_col, sf::Vector2f start_point, bool player_right);
    void insertBox(int pos, sf::RectangleShape box);
    int getNumBoxes();
    sf::ConvexShape getPlayerArea();
    std::vector<sf::RectangleShape> getBorderBoxes(bool p_right);
    sf::RectangleShape removeBox(size_t y_location);
    void addBox(sf::RectangleShape box, size_t y_location);
    bool hitTopBottom(sf::CircleShape ball);
    bool hitHomeEdge(sf::CircleShape ball);

private:
    std::vector<std::vector<sf::RectangleShape>> boxes;
    sf::ConvexShape player_area;
    bool p_right;
    sf::Color box_colour;
    void reconstructPlayerArea();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        for (const auto& row : boxes) {
            for (const auto& rect : row) {
                target.draw(rect, states);
                target.draw(player_area, states);
            }
        }
    }
};

class Ball : public sf::Drawable, public sf::Transformable {
public:
    void load(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel);
    void move();
    void bounce(sf::Vector2f dir);
    sf::Vector2f get_vector();
    sf::CircleShape get_ball();

private:
    sf::CircleShape p_ball;
    sf::Vector2f vel;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p_ball, states);
    }
};


class Paddle : public sf::Drawable, public sf::Transformable {
public:
    void load(sf::Vector2f start_pos, sf::Color pl_col);
    void move();

private:
    sf::RectangleShape paddle;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(paddle, states);
    }
};


class Player : public sf::Drawable {
public:
    Player(sf::RectangleShape player_area, sf::Color pl_col, sf::Color grid_colour, sf::Vector2f top_corner, bool player_right, char* name);
    void move();
    void detectCollision(Player *opponent);
    sf::Text getScore();
    void swapBox(Player *opponent, size_t hit_location);
    std::vector<sf::RectangleShape> getEdgeBoxes();
    sf::RectangleShape removeBox(size_t y_location);
    void addBox(sf::RectangleShape box, size_t y_location);

private:
    int score = 0;
    Paddle p_paddle;
    Ball p_ball;
    GridMap p_grid;
    bool p_right;
    char* p_name;


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p_grid, states);
        //target.draw(p_paddle, states);
        target.draw(p_ball, states);
    }
};
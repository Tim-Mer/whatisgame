#pragma once
#include "config.hpp"

class GridMap : public sf::Drawable
{
public:
    void load(int width, int height);

private:
    std::vector<std::vector<sf::RectangleShape>> boxes;
    sf::RectangleShape boundary;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        for (const auto& row : boxes) {
            for (const auto& rect : row) {
                target.draw(rect, states);
            }
        }
    }
};

class Ball : public sf::Drawable, public sf::Transformable
{
public:
    void load(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel);
    void move(sf::Vector2f vec);

private:
    sf::CircleShape p_ball;
    sf::Vector2f vel;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p_ball, states);
    }
};


class Paddle : public sf::Drawable, public sf::Transformable
{
public:
    void load(sf::Vector2f start_pos, sf::Color pl_col);
    void move();

private:
    sf::RectangleShape paddle;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(paddle, states);
    }
};


class Player : public sf::Drawable 
{
public:
    Player(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel);
    void move();

private:
    int score;
    Paddle p_paddle;
    Ball p_ball;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p_paddle, states);
        target.draw(p_ball, states);
    }
};
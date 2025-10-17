#pragma once
#include "config.hpp"

class GridMap : public sf::Drawable
{
public:
    void load(int width, int height) {
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
    void load(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel) {
        p_ball.setFillColor(pl_col);
        p_ball.setRadius(4.f);
        p_ball.setOutlineThickness(1.f);
        p_ball.setOutlineColor(BLACK);
        p_ball.setPosition(start_pos);
        p_ball.move(init_vel);
    }

    void move(sf::Vector2f vec) {
        vel+=vec;
        p_ball.move(vel);
    }

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
    void load(sf::Vector2f start_pos, sf::Color pl_col) {
        paddle.setSize({5.f, 30.f});
        paddle.setFillColor(pl_col);
        paddle.setPosition(start_pos);
    }

    void move() {
    }

private:
    sf::RectangleShape paddle;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(paddle, states);
    }
};


class Player : public sf::Drawable 
{
public:
    Player(sf::Vector2f start_pos, sf::Color pl_col, sf::Vector2f init_vel){
        p_paddle.load(start_pos, pl_col);
        p_ball.load(start_pos, pl_col, init_vel);
    }

    void move() {
        p_ball.move({1.f, 1.f});
    }
private:
    int score;
    Paddle p_paddle;
    Ball p_ball;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p_paddle, states);
        target.draw(p_ball, states);
    }
};
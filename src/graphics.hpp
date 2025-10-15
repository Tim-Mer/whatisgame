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

class Balls : public sf::Drawable, public sf::Transformable
{
public:
    void load(sf::Vector2f p1, sf::Vector2f p2) {
        c1.setFillColor(PURPLE);
        c2.setFillColor(ORANGE);

        c1.setRadius(4.f);
        c2.setRadius(4.f);

        c1.setOutlineThickness(1.f);
        c2.setOutlineThickness(1.f);

        c1.setOutlineColor(BLACK);
        c2.setOutlineColor(WHITE);

        c1.setPosition(p1);
        c2.setPosition(p2);
    }

    void move() {
        c1.move({1.f, 1.f});
        c2.move({-1.f, -1.f});
    }

private:
    sf::CircleShape c1;
    sf::CircleShape c2;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(c1, states);
        target.draw(c2, states);
    }
};


class Paddles : public sf::Drawable, public sf::Transformable
{
public:
    void load() {
        p1.setSize({5.f, 30.f});
        p2.setSize({5.f, 30.f});

        p1.setFillColor(PURPLE);
        p2.setFillColor(ORANGE);

        p1.setPosition({2.f, 1.f});
        p2.setPosition({WINDOW_WIDTH - 8.f, 1.f});
    }

    void move() {
    }

private:
    sf::RectangleShape p1;
    sf::RectangleShape p2;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(p1, states);
        target.draw(p2, states);
    }
};

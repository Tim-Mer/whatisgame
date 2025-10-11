#pragma once
#include "config.hpp"

class GridMap : public sf::Drawable
{
public:
    // add functions to play with the entity's geometry / colors / texturing...
    void load(int width, int height) {
        for (size_t i=0; i<height; i++) {
            std::vector<sf::RectangleShape> row;
            for (size_t j=0; j<width; j++) {
                sf::RectangleShape cb({10.f, 10.f});
                if (j>(width/2)) {
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
    // add functions to play with the entity's geometry / colors / texturing...
    void load(int width, int height) {//TODO: Change to be Vector2f locations for the starting positions
        c1.setFillColor(PURPLE);
        c2.setFillColor(ORANGE);

        c1.setRadius(4.f);
        c2.setRadius(4.f);

        c1.setOutlineThickness(1.f);
        c2.setOutlineThickness(1.f);
        c1.setOutlineColor(BLACK);
        c2.setOutlineColor(BLACK);
    }

private:
    sf::CircleShape c1;
    sf::CircleShape c2;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(c1, states);
        target.draw(c2, states);
    }
};

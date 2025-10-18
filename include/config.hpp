#pragma once

// Includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

// Window constraints
const int WINDOW_WIDTH=720;
const int WINDOW_HEIGHT=720;

const sf::String WINDOW_NAME = "whatisgame";

// Game styles
//const sf::Font GAME_FONT("res/Gidole-Regular.ttf");
const sf::Color ORANGE(250, 165, 0);
const sf::Color PURPLE(128, 0, 128);
const sf::Color BLACK(0, 0, 0);
const sf::Color WHITE(255, 255, 255);

// Game Settings
const int MAX_SPEED = 5;

// Debug
const bool ENABLE_GRID = false;

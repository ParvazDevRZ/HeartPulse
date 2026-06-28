#pragma once

#include <SFML/Graphics.hpp>

struct Particle
{
    sf::CircleShape shape;
    sf::Color color;

    float x;
    float y;
    float z;

    float radius;
    float offset;
    float speed;

    
};
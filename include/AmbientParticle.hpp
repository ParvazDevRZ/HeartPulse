#pragma once

#include <SFML/Graphics.hpp>


struct AmbientParticle
{
    sf::CircleShape shape;

    float x;
    float y;

    float alpha;

    float speed;

    float size;

    float phase;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Particle.hpp"

class Heart
{
public:

    Heart();

    void update(float pulse);
    
    void draw(sf::RenderTarget& target);

private:

    void createParticles();

    std::vector<Particle> particles;

    float pulse = 1.0f;
};
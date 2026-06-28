#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "AmbientParticle.hpp"


class AmbientSystem
{
private:

    std::vector<AmbientParticle> particles;


public:

    AmbientSystem();


    void update(float time);

    void draw(sf::RenderTarget& target);

};
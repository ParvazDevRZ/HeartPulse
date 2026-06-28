#include "AmbientSystem.hpp"
#include <cmath>
#include <cstdlib>


AmbientSystem::AmbientSystem()
{
    for(int i = 0; i < 200; i++)
    {
        AmbientParticle p;


        p.shape = sf::CircleShape(p.size);

        p.shape.setFillColor(
            sf::Color(255, 80, 120, 180)
        );


        p.x = (rand() % 600) - 300;

        p.y = (rand() % 400) - 200;


        p.alpha = 100 + rand() % 155;


        p.speed = 0.2f + (rand() % 100) / 200.0f;

        p.size = 1.0f + (rand() % 20) / 10.0f;

        p.phase = (rand() % 628) / 100.0f;


        particles.push_back(p);
    }
}


void AmbientSystem::update(float time)
{
    for(auto &p : particles)
    {
        p.y -= p.speed;
        p.x += sin(time + p.phase) * 0.05f;


        if(p.y < -250)
        {
            p.y = 250;
        }
    }
}


void AmbientSystem::draw(sf::RenderTarget& target)
{
    for(auto &p : particles)
    {
        p.shape.setPosition(
            400 + p.x,
            300 + p.y
        );

        int alpha = static_cast<int>(

            120 + sin(p.phase) * 80
        );

        p.shape.setFillColor(
            sf::Color(

                255,
                80,
                120,
                alpha
            )
        );
        target.draw(p.shape);
    }
}
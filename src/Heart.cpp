#include "Heart.hpp"

#include <cmath>
#include <cstdlib>

constexpr float CENTER_X = 400.0f;
constexpr float CENTER_Y = 300.0f;
constexpr float HEART_SCALE = 10.0f;
constexpr int PARTICLE_COUNT = 5500;
constexpr float PARTICLE_RADIUS = 1.5f;

Heart::Heart()
{
    createParticles();
}

void Heart::createParticles()
{
    for(int i = 0; i < PARTICLE_COUNT; i++)
    {
        float t = (rand() % 628) / 100.0f;

        float s = sin(t);
        float x = 16 * s * s * s;

        float y = 13 * cos(t)
                - 5 * cos(2 * t)
                - 2 * cos(3 * t)
                - cos(4 * t);

        float layer = (rand() % 1000) / 1000.0f;

        float scale;

        float r = (rand() % 1000) / 1000.0f;

        if(layer < 0.60f)
        {
            scale = 0.82f + 0.18f * sqrt(r);
        }
        else
        {
            scale = 0.35f + 0.45f * sqrt(r);
        }

        x *= scale;
        y *= scale;

        float distance = sqrt(x * x + y * y);

        float intensity = 1.0f - (distance / 20.0f);

        if (intensity < 0.0f)
            intensity = 0.0f;

        float radius = PARTICLE_RADIUS * (1.2f - distance / 20.0f);

        if (radius < 0.8f)
            radius = 0.8f;

        Particle p;

        p.offset = (rand() % 100) / 500.0f;

        p.radius = radius;

        p.shape = sf::CircleShape(p.radius);

        int red   = 255;
        int green = static_cast<int>(40 + intensity * 70);
        int blue  = static_cast<int>(60 + intensity * 90);

        p.color = sf::Color(red, green, blue);

        p.shape.setFillColor(p.color);

        p.x = x;
        p.y = y;

        p.z = (rand() % 100) / 100.0f;

        p.speed = 0.5f + (rand() % 100) / 200.0f;

        particles.push_back(p);

        if ((rand() % 100) < 30)
        {
            Particle core = p;

            float inner = 0.55f + (rand() % 1000) / 2200.0f;

            core.x *= inner;
            core.y *= inner;

            core.radius *= 0.85f;
            core.shape.setRadius(core.radius);

            particles.push_back(core);
        }
    }
}

void Heart::update(float pulse)
{
    this->pulse = pulse;
}

void Heart::draw(sf::RenderTarget& target)
{
    for (auto &p : particles)
    {
        float currentPulse = pulse + p.offset;

        float depthOffset = p.z * 4.0f;

        p.shape.setPosition(
            CENTER_X + p.x * HEART_SCALE * currentPulse - depthOffset,
            CENTER_Y - p.y * HEART_SCALE * currentPulse - depthOffset
        );

        float depth = 0.8f + p.z * 0.4f;
        p.shape.setRadius(p.radius * depth);

        float dist = std::sqrt(p.x * p.x + p.y * p.y);

        float centerGlow = 1.0f - std::min(dist / 10.0f, 1.0f);

        float glow = p.z * 70.0f;

        glow += centerGlow * 30.0f * pulse;

        int red = 255;
        int green = static_cast<int>(40 + glow);
        int blue = static_cast<int>(70 + glow);

        if (green > 255) green = 255;
        if (blue > 255) blue = 255;

        p.shape.setFillColor(
            sf::Color(red, green, blue)
        );

        target.draw(p.shape);
    }
}
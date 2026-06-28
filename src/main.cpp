#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "Particle.hpp"
#include "Heart.hpp"
#include "AmbientSystem.hpp"

using namespace std;

float heartbeat(float time)
{
    float t = fmod(time, 1.2f);

    float pulse = 1.0f;

    pulse += 0.12f * exp(-80.0f * (t - 0.15f) * (t - 0.15f));

    pulse += 0.08f * exp(-120.0f * (t - 0.32f) * (t - 0.32f));

    return pulse;
}

int main()
{
    if (!sf::Shader::isAvailable())
    {
        cout << "Shaders are NOT supported!" << endl;
        return -1;
    }

    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "HeartBeat"
    );

    window.setFramerateLimit(60);

    sf::RenderTexture heartTexture;

    if (!heartTexture.create(800, 600))
    {
        cout << "RenderTexture failed!" << endl;
        return -1;
    }

    sf::Shader glowShader;

    if (!glowShader.loadFromFile("shaders/glow.frag", sf::Shader::Fragment))
    {
        cout << "Failed to load shader!" << endl;
    } 

    Heart heart;

    AmbientSystem ambient;

    vector<Particle> particles;

    for(int i = 0; i < 2000; i++)
    {
        float t = (rand() % 628) / 100.0f;

        float x = 16 * pow(sin(t), 3);

        float y = 13 * cos(t)
                - 5 * cos(2 * t)
                - 2 * cos(3 * t)
                - cos(4 * t);

        float scale = (rand() % 100) / 100.0f;

        x *= scale;
        y *= scale;

        Particle p;

        p.shape = sf::CircleShape(1.5f);

        p.shape.setFillColor(sf::Color(255,50,80));

        p.x = x;
        p.y = y;

        particles.push_back(p);
}
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        float time = clock.getElapsedTime().asSeconds();

        float pulse = heartbeat(time);

        heart.update(pulse);

        ambient.update(time);

        window.clear(sf::Color::Black);


        heartTexture.clear(sf::Color::Transparent);

        heart.draw(heartTexture);

        ambient.draw(heartTexture);

        heartTexture.display();


        sf::Sprite heartSprite(heartTexture.getTexture());

        window.draw(heartSprite, &glowShader);


        window.display();
    }

    return 0;
}
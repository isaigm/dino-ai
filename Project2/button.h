#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#ifndef BUTTON_H
#define BUTTON_H
static const sf::IntRect buttonFrames[] = 
{
    {6, 70, 27, 28},
    {42, 70, 27, 28},
    {76, 71, 31, 27},
    {110, 68, 36, 32},
    {146, 68, 36, 32},
    {182, 68, 36, 32},
    {218, 68, 36, 32},
    {254, 68, 36, 32},
};
class Button
{
public:
    Button(sf::Texture &texture)
    {
        sp.setTexture(texture);
        sp.setTextureRect(buttonFrames[0]);
        sp.setPosition({WIDTH / 2 - 18, HEIGHT / 2 - 50});
    }
    void draw(sf::RenderTarget &target)
    {
        target.draw(sp);
    }
    void animate(float dt)
    {
        total_dt += dt;
        if (total_dt >= (1 / 5.0f))
        {
            if (curr_frame >= sizeof(buttonFrames) / sizeof(sf::IntRect))
                return;
            sp.setTextureRect(buttonFrames[curr_frame++]);
            total_dt = 0;
        }
    }
    void restart()
    {
        curr_frame = 0;
    }

private:
    sf::Sprite sp;
    float total_dt = 0;
    int curr_frame = 0;
};
#endif
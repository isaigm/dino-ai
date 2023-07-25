#include "../include/cactus_spawner.h"
#include "../include/utils.h"
#include <iostream>
CactusSpawner::CactusSpawner(int n, sf::Texture& spritesheet_) : Spawner(n), spritesheet(spritesheet_)
{
    init();
}

void CactusSpawner::relocate(Background& bg)
{
    for (auto& cactus : objects)
    {
        if (!bg.contains(cactus))
        {
            cactus.setTextureRect(cactusFrames[get_random_number(0, N_CACTUS - 1)]);
            lastCoords += get_random_number(2, 3) * MIN_SEPARATION;
            setCactusPos(cactus, lastCoords);
        }
    }
}
void CactusSpawner::init()
{
    lastCoords = WIDTH / 2;
    for (int i = 0; i < sizeObjects; i++)
    {
        sf::Sprite cactus(spritesheet);
        cactus.setTextureRect(cactusFrames[get_random_number(0, N_CACTUS - 1)]);
        setCactusPos(cactus, lastCoords);
        lastCoords += get_random_number(2, 3) * MIN_SEPARATION;
        objects.push_back(std::move(cactus));
    }
}
void CactusSpawner::restart()
{
    Spawner::restart();
    init();
}
void CactusSpawner::setCactusPos(sf::Sprite& cactus, float x)
{
    
    cactus.setPosition({ x, GROUND - cactus.getGlobalBounds().height });
}
sf::FloatRect CactusSpawner::getNextCactus(Player& p)
{
    float minDist = 1000000;
    sf::FloatRect result;
    for (auto& cactus : objects)
    {
        float dist = cactus.getPosition().x - p.getX();
        if (dist > 0 && dist < minDist)
        {
            minDist = dist;
            result = cactus.getGlobalBounds();
        }
    }
    return result;
}
bool CactusSpawner::collidesWithPlayer(Player &p)
{
    for (auto& cactus : objects)
    {
        if (p.collidesWith(cactus)) return true;
    }
    return false;
}

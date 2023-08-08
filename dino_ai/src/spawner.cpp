#include "../include/spawner.h"
#include "../include/utils.h"
Spawner::Spawner(int n) : sizeObjects(n)
{
}

void Spawner::restart()
{
    objects.erase(objects.begin(), objects.end());
}

void Spawner::render(sf::RenderTarget& rt)
{
    for (auto& obj : objects)
    {
        rt.draw(obj);
    }
}
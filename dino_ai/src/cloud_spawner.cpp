#include "../include/cloud_spawner.h"
#include "../include/utils.h"
CloudSpawner::CloudSpawner(int n, sf::Texture &spritesheet_) : Spawner(n), spritesheet(spritesheet_)
{
    init();
}

void CloudSpawner::relocate(Background& bg)
{
    for (auto& cloud : objects)
    {
        if (!bg.contains(cloud))
        {
            cloud.setPosition({ bg.getView().getCenter().x + WIDTH / 2 + 3 * cloudFrame.width, float(get_random_number(0, 30)) });
        }
    }
}
void CloudSpawner::init()
{
    float last_coords = WIDTH + 20;
    for (int i = 0; i < sizeObjects; i++)
    {
        sf::Sprite cloud(spritesheet);
        cloud.setTextureRect(cloudFrame);
        cloud.setPosition({ last_coords, float(get_random_number(0, 20)) });
        last_coords += get_random_number(2, 4) * cloudFrame.width;
        objects.push_back(std::move(cloud));
    }
}
void CloudSpawner::restart()
{
    Spawner::restart();
    init();
}
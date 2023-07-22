#include "../include/cloud_manager.h"
#include "../include/utils.h"
CloudManager::CloudManager(int n, sf::Texture &spritesheet_, Background &sky_) : spritesheet(spritesheet_), sky(sky_), sizeClouds(n)
{
    init();
}
void CloudManager::init()
{
    float last_coords = WIDTH + 20;
    for (int i = 0; i < sizeClouds; i++)
    {
        sf::Sprite cloud(spritesheet);
        cloud.setTextureRect(cloudFrame);
        cloud.setPosition({ last_coords, float(get_random_number(0, 20)) });
        last_coords += get_random_number(2, 4) * cloudFrame.width;
        clouds.push_back(std::move(cloud));
    }
}
void CloudManager::restart()
{
    clouds.erase(clouds.begin(), clouds.end());
    init();
}

void CloudManager::update()
{
    for (auto& cloud : clouds)
    {
        if (!sky.contains(cloud))
        {
            cloud.setPosition({ sky.getView().getCenter().x + WIDTH / 2 + 3 * cloudFrame.width, float(get_random_number(0, 30)) });
        }
    }
}
void CloudManager::render(sf::RenderTarget& rt)
{
    for (auto& cloud : clouds)
    {
        rt.draw(cloud);
    }
}
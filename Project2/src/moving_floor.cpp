#include "../include/moving_floor.h"
#include "../include/constants.h"
MovingFloor::MovingFloor(sf::Texture& spritesheet, float speed_) : speed(speed_), currFloor(spritesheet)
{
    currFloor.setTextureRect(sf::IntRect(2, 53, FLOOR_WIDTH, 15));
    currFloor.setPosition({ 0, HEIGHT / 2 });
    nextFloor = currFloor;
}
void MovingFloor::render(sf::RenderTarget& rt)
{
    rt.draw(currFloor);
    rt.draw(nextFloor);
}
void MovingFloor::update(float dt)
{
    traveledDistance += speed * dt;
    if (traveledDistance >= FLOOR_WIDTH - WIDTH)
    {
        if (mainBg)
        {
            nextFloor.setPosition({ nextPosition, HEIGHT / 2 });
        }
        else
        {
            currFloor.setPosition({ nextPosition, HEIGHT / 2 });
        }
        nextPosition += FLOOR_WIDTH;
        mainBg = !mainBg;
        traveledDistance = -(FLOOR_WIDTH - traveledDistance);
    }
}
void MovingFloor::restart()
{
    currFloor.setPosition({ 0, HEIGHT / 2 });
    nextPosition = FLOOR_WIDTH;
    mainBg = true;
    traveledDistance = 0;
}
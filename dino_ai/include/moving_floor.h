#include <SFML/Graphics.hpp>
#ifndef MOVING_FLOOR_H
#define MOVING_FLOOR_H
class MovingFloor
{
public:
	MovingFloor(sf::Texture& spritesheet, float speed);
	void render(sf::RenderTarget& rt);
	void update(float dt);
	void restart();
	void setSpeed(float speed);
private:
	sf::Sprite currFloor, nextFloor;
	float traveledDistance = 0; // para saber que tanto del fondo actual, que mide 1200 pixeles de ancho, se ha recorrido
	bool mainBg = true;
	const float FLOOR_WIDTH = 1200;
	float nextPosition = FLOOR_WIDTH, speed;
};
#endif 

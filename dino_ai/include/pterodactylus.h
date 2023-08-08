#include <SFML/Graphics.hpp>
#ifndef PTERODACTYLUS_H
#define PTERODACTYLUS_H
static const sf::IntRect frames[] = { {134, 8, 46, 34}, {180, 2, 46, 30} };
class Pterodactylus
{
public:
	Pterodactylus(sf::Texture& spritesheet);
	void update(float dt);
	void render(sf::RenderTarget& rt);
	void animate(float dt);
private:
	float x, y;
	float speed;
	sf::Sprite sp;
	float totalDt = 0;
	int currFrame = 0;
};
#endif // !PTERODACTYLUS_H

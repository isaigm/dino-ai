#include "../include/pterodactylus.h"

Pterodactylus::Pterodactylus(sf::Texture& spritesheet)
{
	sp.setTexture(spritesheet);
	sp.setTextureRect(frames[currFrame]);
}

void Pterodactylus::update(float dt)
{
	x += speed * dt;
	sp.setPosition({ x, y });
}

void Pterodactylus::render(sf::RenderTarget& rt)
{
	rt.draw(sp);
}
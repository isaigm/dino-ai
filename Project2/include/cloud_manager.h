#ifndef CLOUD_MANAGER
#define CLOUD_MANAGER
#include <vector>
#include <SFML/Graphics.hpp>
#include "background.h"
static const sf::IntRect cloudFrame = { 86, 1, 46, 17 };
class CloudManager
{
public:
	CloudManager(int n, sf::Texture &spritesheet, Background&sky);
	void update();
	void restart();
	void render(sf::RenderTarget& rt);
private:
	void init();
	std::vector<sf::Sprite> clouds;
	Background& sky;
	sf::Texture& spritesheet;
	int sizeClouds;
};

#endif 
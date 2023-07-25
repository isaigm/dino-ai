#include "background.h"
#include <vector>
#include <SFML/Graphics.hpp>
#ifndef SPAWNER_H
#define SPAWNER_H

class Spawner
{
public:
	Spawner(int n);
	virtual void relocate(Background& bg) = 0;
	virtual void restart();
	void render(sf::RenderTarget& rt);
protected:

	std::vector<sf::Sprite> objects;
	int sizeObjects;
};

#endif 
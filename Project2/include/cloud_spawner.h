#include "../include/spawner.h"
#ifndef CLOUD_SPAWNER_H
#define CLOUD_SPAWNER_H
static const sf::IntRect cloudFrame = { 86, 1, 46, 17 };
class CloudSpawner : public Spawner
{
public:
	CloudSpawner(int n, sf::Texture &spritesheet);
	virtual void relocate(Background& bg) override;
	virtual void restart() override;
private:
	void init();
	sf::Texture& spritesheet;

};
#endif // !CLOUD_SPAWNER_H

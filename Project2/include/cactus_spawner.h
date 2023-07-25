#include "../include/spawner.h"
#include "../include/player.h"
#ifndef CACTUS_SPAWNER_H
#define CACTUS_SPAWNER_H
static const sf::IntRect cactusFrames[] =
{ {228, 2, 17, 35},
 {245, 2, 34, 35},
 {279, 2, 51, 35},
 {332, 2, 49, 50},
 {382, 2, 25, 50},
 {407, 2, 75, 50} };
static const int N_CACTUS = sizeof(cactusFrames) / sizeof(sf::IntRect);
static const float GROUND = 125 + 47;
static float MIN_SEPARATION = 100;
class CactusSpawner : public Spawner
{
public:
	CactusSpawner(int n, sf::Texture& spritesheet);
	sf::FloatRect getNextCactus(Player &p);
	bool collidesWithPlayer(Player& p);
	virtual void relocate(Background& bg) override;
	virtual void restart() override;
private:
	void init();
	void setCactusPos(sf::Sprite& cactus, float x);
	sf::Texture& spritesheet;
	float lastCoords;
};
#endif

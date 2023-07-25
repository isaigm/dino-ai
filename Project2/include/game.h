#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "background.h"
#include "constants.h"
#include "score.h"
#include "cloud_spawner.h"
#include "cactus_spawner.h"
#include "moving_floor.h"
static const int N_CLOUDS = 5;
static const int POPULATION_SIZE = 100;
static const sf::IntRect GAME_OVER_FRAME = { 655, 15, 191, 11 };
static float playerSpeed = 200;

class Game
{
public:
	Game(sf::Texture& spritesheet);
	void run();
private:
	void events();
	void update(float dt);
	void render(float dt);
	void setCactusCoords(float x);
	void restartPlayers();
	void updatePlayers(float);
	void renderPlayers();
	int  deadPlayers();
	void applyGeneticAlgo();
	sf::Texture &spritesheet;
	Score score;
	Background ground;
	Background sky;
	sf::RenderWindow window;
	bool gameOver = false;
	std::vector<Player> population;
	MovingFloor movingFloor;
	CloudSpawner cloudSpawner;
	CactusSpawner cactusSpawner;
};
#endif
#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "background.h"
#include "constants.h"
#include "score.h"
#include "cloud_spawner.h"
#include "cactus_spawner.h"
#include "moving_floor.h"
#include "info.h"
static const int N_CLOUDS = 5;
static const int POPULATION_SIZE = 1000;
static const sf::IntRect GAME_OVER_FRAME = { 655, 15, 191, 11 };
static float playerSpeed = 200;

class Game
{
public:
	Game();
	void run();
	const Info &getInfo();
private:
	void events();
	void update(float dt);
	void render(float dt);
	void restartPlayers();
	void updatePlayers(float);
	void renderPlayers();
	void applyGeneticAlgo();
	sf::Texture spritesheet;
	Info info;
	bool gameOver = false;
	Score score;
	Background ground;
	Background sky;
	sf::RenderWindow window;
	sf::Font font;
	sf::Text infoText;
	std::vector<Player> population;
	MovingFloor movingFloor;
	CloudSpawner cloudSpawner;
	CactusSpawner cactusSpawner;
};
#endif
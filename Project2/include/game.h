#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "background.h"
#include "sfx.h"
#include "button.h"
#include "constants.h"
#include "score.h"
#include "cloud_manager.h"
static const int N_CLOUDS = 5;
static const float GROUND = 125 + 47;
static const int POPULATION_SIZE = 100;
static const sf::IntRect cactusFrames[] =
{ {228, 2, 17, 35},
 {245, 2, 34, 35},
 {279, 2, 51, 35},
 {332, 2, 49, 50},
 {382, 2, 25, 50},
 {407, 2, 75, 50} };
static const sf::IntRect GAME_OVER_FRAME = { 655, 15, 191, 11 };
static const int N_CACTUS = sizeof(cactusFrames) / sizeof(sf::IntRect);
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
	CloudManager cloudManager;
	Score score;
	Button btn;

	Background ground;
	Background sky;
	sf::RenderWindow window;
	sf::Sprite bg; 
	sf::Sprite gameOverScreen, cactus;

	float distX = 0; // para saber que tanto del fondo actual, que mide 1200 pixeles de ancho, se ha recorrido
	bool mainBg = true;
	bool gameOver = false;
	float nextCoords = 1200;
	sf::Sprite nextBg;
	std::vector<Player> population;
};
#endif
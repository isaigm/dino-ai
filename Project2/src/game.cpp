#include "../include/game.h"
#include "../include/utils.h"
#include <iostream>
Game::Game(sf::Texture& spritesheet_) : spritesheet(spritesheet_), score(spritesheet_), cactusSpawner(4, spritesheet_), ground(sf::FloatRect(0, 12, WIDTH, HEIGHT / 2), playerSpeed),
sky(sf::FloatRect(0, 0, WIDTH, HEIGHT / 2), 25), movingFloor(spritesheet_, playerSpeed), cloudSpawner(N_CLOUDS, spritesheet_), window(sf::VideoMode(WIDTH, HEIGHT), "Training FNN")
{
	window.setVerticalSyncEnabled(true);
    ground.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    sky.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    population.reserve(POPULATION_SIZE);
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        population.emplace_back(spritesheet);
    }
}
void Game::run()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		events();
		update(dt);
		render(dt);
	}
}
void Game::events()
{
    sf::Event ev;
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Q)
            {
                for (auto& player : population) if(!player.hasDead()) player.score = score.getScore();
                gameOver = true;
            }
        default:
            break;
        }
    }
}
void Game::render(float dt)
{
    window.clear(sf::Color::White);
    window.setView(sky.getView());
    cloudSpawner.render(window);
    window.setView(ground.getView());
    movingFloor.render(window);
    renderPlayers();
    cactusSpawner.render(window);
    window.setView(window.getDefaultView());
    score.draw(window);
    window.display();
}
void Game::renderPlayers()
{
    for (auto& player : population)
    {
        player.draw(window);
    }
}
void Game::update(float dt)
{
    if (gameOver)
    {
        applyGeneticAlgo();
        gameOver = false;
        playerSpeed = 200;
        score.restart();
        restartPlayers();
        movingFloor.restart();
        cloudSpawner.restart();
        cactusSpawner.restart();
        sky.getView().setCenter({ WIDTH / 2, 80 });
        ground.getView().setCenter({ WIDTH / 2, 92 });
      
        return;
    }
    ground.setSpeed(playerSpeed);
    score.update(dt);
    sky.update(dt);
    ground.update(dt);
    movingFloor.update(dt);
    updatePlayers(dt);
    gameOver = deadPlayers() == POPULATION_SIZE;
    cloudSpawner.relocate(sky);
    cactusSpawner.relocate(ground);
    
}

void Game::restartPlayers()
{
    for (auto& player : population)
    {
        player.restart();
    }
}
void Game::updatePlayers(float dt)
{
    for (auto& player : population)
    {
        if (!player.hasDead())
        {
            auto nextCactus = cactusSpawner.getNextCactus(player);
            float dist = nextCactus.getPosition().x - player.getX();
            float cactusWidth = nextCactus.getSize().x / 75.0f;
            player.makeMove(dist / 1000.0f, cactusWidth);
            player.update(dt);
            player.animate(dt);
            if(cactusSpawner.collidesWithPlayer(player))
            {
               player.die();
               player.score = score.getScore();
            }
        }
    }
}
int Game::deadPlayers()
{
    int cnt = 0;
    for (auto& player : population)
    {
        if (player.hasDead()) cnt++;
    }
    return cnt;
}
void Game::applyGeneticAlgo()
{
    std::sort(population.begin(), population.end(), [](auto &p1, auto p2)
        { return p1.score > p2.score; });
    int parents = get_random_number(20, 40);
    std::vector<Player> nextGen;
    for (int i = 0; i < parents; i++)
    {
        nextGen.push_back(population[i]);
    }
    for (int i = 0; i < POPULATION_SIZE - parents; i++)
    {
        int i1 = rand() % population.size();
        int i2 = rand() % population.size();
        Player newPlayer(spritesheet);
        newPlayer.crossover(population[i1], population[i2]);
        if (rand() % 10 < 3)
            newPlayer.mutate();
        
        nextGen.push_back(std::move(newPlayer));
    }
    population = std::move(nextGen);
}
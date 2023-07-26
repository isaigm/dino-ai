#include "../include/game.h"
#include "../include/utils.h"
#include <iostream>
Game::Game() : score(spritesheet), cactusSpawner(4, spritesheet), ground(sf::FloatRect(0, 12, WIDTH, HEIGHT / 2), playerSpeed),
sky(sf::FloatRect(0, 0, WIDTH, HEIGHT / 2), 25), movingFloor(spritesheet, playerSpeed), cloudSpawner(N_CLOUDS, spritesheet), window(sf::VideoMode(WIDTH, HEIGHT), "Training FNN")
{
    const char* SPRITESHEET_FILE = "sprites.png";
    const char* FONT_FILE = "font.ttf";
    if (!spritesheet.loadFromFile(SPRITESHEET_FILE) || !font.loadFromFile(FONT_FILE))
    {
        std::cerr << "no se pudo cargar algun archivo de recursos\n";
        exit(-1);
    }
    info.maxPopulation = POPULATION_SIZE;
    infoText.setFont(font);
    infoText.setPosition(10, 200);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::White);
	window.setVerticalSyncEnabled(true);
    ground.getView().setViewport(sf::FloatRect(0, 0, 1.0f, 0.5f));
    sky.getView().setViewport(sf::FloatRect(0, 0, 1.0f, 0.5f));
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
        window.setTitle(std::to_string(1.0f / dt));
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
                for (auto& player : population) if(!player.hasDied()) player.score = score.getScore();
                gameOver = true;
            }
        default:
            break;
        }
    }
}
void Game::render(float dt)
{
    window.clear(sf::Color::Black);
    window.setView(sky.getView());
    cloudSpawner.render(window);
    window.setView(ground.getView());
    movingFloor.render(window);
    renderPlayers();
    cactusSpawner.render(window);
    window.setView(window.getDefaultView());
    score.draw(window);
    char data[256];
    snprintf(data, sizeof(data), "Pop size: %d\nCurrent generation: %d\nBest score: %d\nAlive players: %d", info.maxPopulation, info.currentGen, info.bestScore, info.alivePlayers);
    infoText.setString(data);
    window.draw(infoText);
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
        info.currentGen++;
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
    int fPlayers = deadPlayers();
    gameOver = fPlayers == POPULATION_SIZE;
    info.alivePlayers = POPULATION_SIZE - fPlayers;
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
        if (!player.hasDied())
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
        if (player.hasDied()) cnt++;
    }
    return cnt;
}
void Game::applyGeneticAlgo()
{
    std::sort(population.begin(), population.end(), [](auto &p1, auto &p2)
        { return p1.score > p2.score; });
    int parents = get_random_number(20, 70);
    info.bestScore = std::max(info.bestScore, population[0].score);
  
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
        if (rand() % 10 <= 3)
            newPlayer.mutate();
        
        nextGen.push_back(std::move(newPlayer));
    }
    population = std::move(nextGen);  
}
const Info &Game::getInfo()
{
    return info;
}
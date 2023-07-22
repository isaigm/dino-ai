#include "game.h"
#include "utils.h"
Game::Game(sf::Texture& spritesheet_) : spritesheet(spritesheet_),
btn(spritesheet_), score(spritesheet_), bg(spritesheet_), cactus(spritesheet_), gameOverScreen(spritesheet_), ground(sf::FloatRect(0, 12, WIDTH, HEIGHT / 2), playerSpeed),
sky(sf::FloatRect(0, 0, WIDTH, HEIGHT / 2), 25), cloudManager(N_CLOUDS, spritesheet_, sky), window(sf::VideoMode(WIDTH, HEIGHT), "Training FNN")
{
	window.setVerticalSyncEnabled(true);
    
    cactus.setTextureRect(cactusFrames[get_random_number(0, N_CACTUS - 1)]);
    setCactusCoords(500);
    gameOverScreen.setTextureRect(GAME_OVER_FRAME);
    gameOverScreen.setPosition({ float(WIDTH - GAME_OVER_FRAME.width) / 2, 50 });
    ground.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    sky.getView().setViewport(sf::FloatRect(0, 0, 1, 0.5f));
    bg.setTextureRect(sf::IntRect(2, 53, 1200, 15));
    bg.setPosition({ 0, HEIGHT / 2 });
    nextBg = bg;
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
    cloudManager.render(window);
    window.setView(ground.getView());
    window.draw(bg);
    renderPlayers();
    window.draw(nextBg);
    window.draw(cactus);
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
        bg.setPosition({ 0, HEIGHT / 2 });
        gameOver = false;
        nextCoords = 1200;
        mainBg = true;
        distX = 20;
        playerSpeed = 200;
        score.restart();
        restartPlayers();
        btn.restart();
        cloudManager.restart();
        cactus.setTextureRect(cactusFrames[get_random_number(0, N_CACTUS - 1)]);
        sky.getView().setCenter({ WIDTH / 2, 80 });
        ground.getView().setCenter({ WIDTH / 2, 92 });
        setCactusCoords(500);
        return;
    }
    distX += dt * playerSpeed;
    ground.setSpeed(playerSpeed);
    score.update(dt);
    sky.update(dt);
    ground.update(dt);
    updatePlayers(dt);
    gameOver = deadPlayers() == POPULATION_SIZE;
    if (!ground.contains(cactus))
    {
        cactus.setTextureRect(cactusFrames[get_random_number(0, N_CACTUS - 1)]);
        setCactusCoords(ground.getView().getCenter().x + WIDTH / 2 + 30 + get_random_number(0, 5) * 20);
    }
    cloudManager.update();
    if (distX >= 1200 - WIDTH)
    {
        if (mainBg)
        {
            nextBg.setPosition({ nextCoords, HEIGHT / 2 });
        }
        else
        {
            bg.setPosition({ nextCoords, HEIGHT / 2 });
        }
        nextCoords += 1200;
        mainBg = !mainBg;
        distX = -(1200 - distX);
    }
}
void Game::setCactusCoords(float x)
{
	cactus.setPosition({ x, GROUND - cactus.getGlobalBounds().height });
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
            player.makeMove((cactus.getPosition().x - player.getX()) / 710.0f);
            player.update(dt);
            player.animate(dt);
            if (player.collidesWith(cactus))
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
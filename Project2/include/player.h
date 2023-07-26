#include <SFML/Graphics.hpp>
#include "mlp.h"
#include <random>
#ifndef PLAYER_H
#define PLAYER_H
static const sf::IntRect dinoFrames[] =
{
    {936, 2, 44, 47},
    {980, 2, 44, 47},
    {848, 2, 44, 47}
};
static const sf::IntRect dieFrame = { 1024, 2, 44, 47 };
static const float GRAVITY = 1400.0f;
static std::default_random_engine defEngine;
static std::uniform_real_distribution<float> floatDistro(-0.1, 0.1);
class Player
{
public:
    Player(sf::Texture &texture);
    void crossover(Player& p1, Player& p2);
    void mutate();
    void draw(sf::RenderTarget &target);
    void animate(float dt);
    void update(float dt);
    void restart();
   
    void makeMove(float distTo, float cactusWidth);
    float getX() const;
    float getY() const;
    void die();
    bool collidesWith(sf::Sprite &);
    bool hasDied();
    bool isOnGround = true;
    int score = 0;
    MLP network;
private:
    sf::Sprite sp;
    int currFrame = 0;
    float playerSpeed = 200;
    float totalDt = 0;
    float x, y, ground, ySpeed;
    bool dead = false;   
};
#endif
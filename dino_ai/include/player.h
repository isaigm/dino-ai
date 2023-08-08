#include <SFML/Graphics.hpp>
#include <random>
#include "mlp.h"
#ifndef PLAYER_H
#define PLAYER_H
static const sf::IntRect dinoFrames[] =
{
    {936, 2, 44, 47},
    {980, 2, 44, 47},
    {848, 2, 44, 47}
};
static const sf::IntRect crouchFrames[] =
{
    {1112, 19, 59, 30},
    {1171, 19, 59, 30}
};
static std::random_device rd;
static std::default_random_engine defEngine(rd());
static std::uniform_real_distribution<float> floatDistro(-1.0f, 1.0f);
enum class State
{
    ON_AIR,
    RUNNING,
    CROUCHED
};
enum class Action
{
    JUMP,
    CROUCH,
    NONE
};
class Player
{
public:
    Player(sf::Texture &spritesheet);
    void crossover(Player& p1, Player& p2);
    void mutate();
    void draw(sf::RenderTarget &target);
    void animate(float dt);
    void update(float dt);
    void restart();
    void setSpeed(float speed);
    void makeMove(float distTo, float cactusHeight, float cactusWidth);
    float getX() const;
    float getY() const;
    void die();
    bool collidesWith(sf::Sprite &);
    bool hasDied();
    int score = 0;
    MLP network;
private:
    void moveToGround();
    sf::Sprite sp;
    State currState = State::RUNNING;
    int currFrame = 0;
    float speed = 0;
    float totalDt = 0;
    float x, y, ySpeed;
    bool dead = false;   
    float gravity = 1400.0f;
};
#endif
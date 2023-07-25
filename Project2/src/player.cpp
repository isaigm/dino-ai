#include "../include/player.h"
#include "../include/collision.h"
#include "../include/utils.h"

Player::Player(sf::Texture &texture) : network({2, 20, 20, 2})
{
    sp.setTexture(texture);
    sp.setTextureRect(dinoFrames[currFrame]);
    x = 20;
    ground = y = 125;
    ySpeed = -500;
    sp.setPosition(x, y);
}
void Player::die()
{
    dead = true;
    sp.setTextureRect(dieFrame);
}
bool Player::hasDied()
{
    return dead;
}
void Player::animate(float dt)
{
    totalDt += dt;
    if (totalDt >= (1 / 10.f))
    {
        if (isOnGround)
        {
            sp.setTextureRect(dinoFrames[currFrame]);
            if (++currFrame >= 2)
            {
                currFrame = 0;
            }
        }
        else
        {
            sp.setTextureRect(dinoFrames[2]);
            currFrame = 1;
        }
        totalDt = 0;
    }
}
void Player::update(float dt)
{
    x += playerSpeed * dt;
    if (!isOnGround)
    {
        y += ySpeed * dt;
        ySpeed += GRAVITY * dt;
        if (y >= ground)
        {
            y = ground;
            isOnGround = true;
            ySpeed = -500;
        }
    }
    sp.setPosition({x, y});
}
float Player::getX() const
{
    return x;
}
float Player::getY() const
{
    return y;
}
void Player::restart()
{
    isOnGround = true;
    x = 20;
    y = 125;
    ySpeed = -500;
    playerSpeed = 200;
    dead = false;
    score = 0;
    currFrame = 0;
    sp.setPosition(x, y);
    sp.setTextureRect(dinoFrames[currFrame]);
}

void Player::draw(sf::RenderTarget &target)
{
    target.draw(sp);
}
bool Player::collidesWith(sf::Sprite &entity)
{
    return Collision::PixelPerfectTest(sp, entity);
}

void Player::makeMove(float distTo, float cactusWidth)
{
    Eigen::MatrixXf input(2, 1);
    input(0, 0) = isOnGround;
    input(1, 0) = distTo;

    auto output = network.feedforward(input);
    float jump = output(0, 0);
    float notJump = output(1, 0);
    if (jump > notJump && isOnGround) isOnGround = false;
}
void Player::crossover(Player& p1, Player& p2)
{
    for (int i = 0; i < network.weights.size(); i++)
    {
        auto& mat = network.weights[i];
        auto& p1Mat = p1.network.weights[i];
        auto& p2Mat = p2.network.weights[i];
        auto& bias = network.biases[i];
        auto& p1Bias = p1.network.biases[i];
        auto& p2Bias = p2.network.biases[i];
        int rows = mat.rows();
        int cols = mat.cols();
        for (int i = 0; i < rows; i++)
        {
            int idx = get_random_number(0, cols - 1);
            for (int j = 0; j < idx; j++)
            {
                mat(i, j) = p2Mat(i, j);
            }
            for (int j = idx; j < cols; j++)
            {
                mat(i, j) = p1Mat(i, j);
            }
        }
        int biasSize = bias.rows();
        int idx = get_random_number(0, biasSize - 1);
        for (int i = 0; i < idx; i++)
        {
            bias(i, 0) = p1Bias(i, 0);
        }
        for (int i = idx; i < biasSize; i++)
        {
            bias(i, 0) = p2Bias(i, 0);
        }
    }
}
void Player::mutate()
{
    for (int i = 0; i < network.weights.size(); i++)
    {
        auto& bias = network.biases[i];
        auto& mat = network.weights[i];
        int rows = mat.rows();
        int cols = mat.cols();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {

                mat(i, j) += floatDistro(defEngine);
            }
        }
        for (int i = 0; i < bias.rows(); i++)
        {
            bias(i, 0) += floatDistro(defEngine);
        }
    }
}
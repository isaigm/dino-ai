#include "../include/player.h"
#include "../include/collision.h"
#include "../include/utils.h"
#include "../include/constants.h"
Player::Player(sf::Texture &spritesheet) : network({6, 16, 8, 3})
{
    sp.setTexture(spritesheet);
    sp.setTextureRect(dinoFrames[currFrame]);
    x = 20;
    moveToGround();
    ySpeed = -500;
    sp.setPosition(x, y);
}
void Player::setSpeed(float speed_)
{
    speed = speed_;
}
void Player::die()
{
    dead = true;
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
        switch (currState)
        {
        case State::ON_AIR:
            sp.setTextureRect(dinoFrames[2]);
            currFrame = 1;
            break;
        case State::RUNNING:
            sp.setTextureRect(dinoFrames[currFrame]);
            currFrame++;
            if (currFrame > 2)
            {
                currFrame = 0;
            }
            break;
        case State::CROUCHED:
            sp.setTextureRect(crouchFrames[currFrame]);
            currFrame++;
            if (currFrame > 1)
            {
                currFrame = 0;
            }
            break;
        default:
            break;
        }
        totalDt = 0;
    }
}
void Player::update(float dt)
{
    x += speed * dt;
    if (currState == State::ON_AIR)
    {
        y += ySpeed * dt;
        ySpeed += gravity * dt;
        if (y >= GROUND - dinoFrames[0].height)
        {
            y = GROUND - dinoFrames[0].height;
            currState = State::RUNNING;
            ySpeed = -500;
            gravity = 1400.0f;
        }
        sp.setPosition({ x, y });
    }
    else moveToGround();
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
    currState = State::RUNNING;
    x = 20;
    ySpeed = -500;
    dead = false;
    score = 0;
    gravity = 1400.0f;
    currFrame = 0;
    sp.setTextureRect(dinoFrames[currFrame]);
    moveToGround();
}
void Player::draw(sf::RenderTarget &target)
{
    target.draw(sp);
}
bool Player::collidesWith(sf::Sprite &entity)
{
    return Collision::PixelPerfectTest(sp, entity);
}
void Player::makeMove(float distTo, float cactusHeight, float cactusWidth)
{
    Eigen::MatrixXf input(6, 1);
    input(0, 0) = float(currState) / 2;
    input(1, 0) = distTo;
    input(2, 0) = cactusWidth;
    input(3, 0) = cactusHeight;
    input(4, 0) = speed / 1000.0f;
    input(5, 0) = y / 125.0f;
    auto output = network.feedforward(input);
    float jump = output(0, 0);
    float crouch = output(1, 0);
    float none = output(2, 0);
    float actions[] = { jump, crouch, none };
    int idxAction = 0;
    float maxAction = -100000;
    for (int i = 0; i < 3; i++)
    {
        if (actions[i] > maxAction)
        {
            maxAction = actions[i];
            idxAction = i;
        }
    }
    Action action = Action(idxAction);
   
    switch (action)
    {
    case Action::JUMP:
        if (currState == State::RUNNING) currState = State::ON_AIR;
        break;
    case Action::CROUCH:
        if (currState == State::ON_AIR) gravity = 3000.0f;
        else if (currState == State::RUNNING) currState = State::CROUCHED;
        break;
    case Action::NONE:
        if (currState == State::CROUCHED) currState = State::RUNNING;
        break;
    default:
        break;
    }
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
        for (int k = 0; k < rows; k++)
        {
            int idx = get_random_number(0, cols - 1);
            for (int j = 0; j < idx; j++)
            {
                mat(k, j) = p2Mat(k, j);
            }
            for (int j = idx; j < cols; j++)
            {
                mat(k, j) = p1Mat(k, j);
            }
        }
        int biasSize = bias.rows();
        int idx = get_random_number(0, biasSize - 1);
        for (int k = 0; k < idx; k++)
        {
            bias(k, 0) = p1Bias(k, 0);
        }
        for (int k = idx; k < biasSize; k++)
        {
            bias(k, 0) = p2Bias(k, 0);
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
        for (int k = 0; k < rows; k++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (get_random_number(0, 9) < 4)
                {
                    mat(k, j) = floatDistro(defEngine) * 16;

                }
            }
        }
        for (int k = 0; k < bias.rows(); k++)
        {
            if (get_random_number(0, 9) < 4)
            {
                bias(k, 0) = floatDistro(defEngine) * 16;

            }
        }
    }
}
void Player::moveToGround()
{
    y = GROUND - sp.getTextureRect().height;
    sp.setPosition({ x, y });
}
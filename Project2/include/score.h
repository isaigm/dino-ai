#include <SFML/Graphics.hpp>
#include <fstream>
#include <array>
#ifndef SCORE_H
#define SCORE_H
static sf::IntRect numbers[] = {
    {655, 2, 9, 11},
    {666, 2, 9, 11},
    {675, 2, 9, 11},
    {685, 2, 9, 11},
    {695, 2, 9, 11},
    {705, 2, 9, 11},
    {715, 2, 9, 11},
    {725, 2, 9, 11},
    {735, 2, 9, 11},
    {745, 2, 9, 11}};
static sf::IntRect hiFrame = {755, 2, 19, 11};
class Score
{
public:
    Score(sf::Texture& texture);
    int getScore();
    void draw(sf::RenderTarget& target);
    void setMaxScore();
    void restart();
    bool hasUpdated();
    void update(float dt);

private:
    void setDigits(int n, std::array<sf::Sprite, 5>& digits);
    void blink(float dt);
    int cnt = 0;
    int score = 0;
    int maxScore = 0;
    bool visible = true;
    bool _100more = false;
    float totalTime = 0;
    float blinkTime = 0;
    std::array<sf::Sprite, 5> scoreDigits;
    std::array<sf::Sprite, 5> maxScoreDigits;
    sf::Sprite hi;
};
#endif
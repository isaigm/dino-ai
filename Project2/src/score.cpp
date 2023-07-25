#include "../include/score.h"
Score::Score(sf::Texture& texture)
{
    hi.setTexture(texture);
    hi.setTextureRect(hiFrame);
    hi.setPosition(430, 10);
    for (int i = 0; i < 5; i++)
    {
        scoreDigits[i].setTexture(texture);
        maxScoreDigits[i].setTexture(texture);
        scoreDigits[i].setTextureRect(numbers[0]);
        scoreDigits[i].setPosition(530 + 11 * i, 10);
        maxScoreDigits[i].setPosition(455 + 11 * i, 10);
    }
    std::ifstream ifs("max_score.txt");
    if (!ifs.is_open())
    {
        std::ofstream ofs("max_score.txt");
        ofs << 0;
        ofs.close();
    }
    else
    {
        ifs >> maxScore;
        ifs.close();
    }
    setDigits(maxScore, maxScoreDigits);
}
int Score::getScore()
{
    return score;
}
void Score::draw(sf::RenderTarget& target)
{
    target.draw(hi);
    for (auto& mdigit : maxScoreDigits)
    {
        target.draw(mdigit);
    }
    if (!visible)
        return;
    for (auto& sdigit : scoreDigits)
    {
        target.draw(sdigit);
    }
}
void Score::setMaxScore()
{
    std::ofstream ofs("max_score.txt");
    ofs << maxScore;
    setDigits(maxScore, maxScoreDigits);
    ofs.close();
}
void Score::restart()
{
    _100more = false;
    score = 0;
    totalTime = 0;
    blinkTime = 0;
    visible = true;
    cnt = 0;
}
bool Score::hasUpdated()
{
    if (_100more)
    {
        _100more = false;
        return true;
    }
    return false;
}
void Score::update(float dt)
{
    if (score % 100 == 0 && score > 0)
    {
        setDigits(score, scoreDigits);
        blink(dt);
        totalTime = 0;
        return;
    }
    totalTime += dt;
    if (totalTime >= 0.1f)
    {
        setDigits(score, scoreDigits);
        maxScore = std::max(maxScore, score);
        score++;
        _100more = score % 100 == 0;
        totalTime = 0;
    }
}

void Score::setDigits(int n, std::array<sf::Sprite, 5>& digits)
{
    for (int i = 0; i < 5; i++)
    {
        int digit = n % 10;
        n /= 10;
        digits[4 - i].setTextureRect(numbers[digit]);
    }
}
void Score::blink(float dt)
{
    if (cnt >= 8)
    {
        score++;
        cnt = 0;
        blinkTime = 0;
        return;
    }
    blinkTime += dt;
    if (blinkTime >= 0.2f) // cada 0.2 s es visible y no visible, por lo tanto este if se cumple dos veces para conseguir un parpadeo
    {                       // queremos 4 parpadeos, por lo tanto son 8 veces que debe pasar por este if
        visible = !visible;
        cnt++;
        blinkTime = 0;
    }
}

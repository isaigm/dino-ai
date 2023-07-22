#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#ifndef SFX_H
#define SFX_H
class Sfx
{
public:
    Sfx(std::string file)
    {
        if (!buffer.loadFromFile(file))
        {
            std::cerr << "no se pudo cargar el archivo de audio\n";
            exit(-1);
        }
        sound.setBuffer(buffer);
    }
    void play()
    {
        sound.play();
    }

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};
#endif
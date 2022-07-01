#pragma once
#include <SFML/Graphics.hpp>

class TexturesManager
{
public:
    static sf::Texture background;
    static sf::Texture start;
    static sf::Texture gameOver;
    static sf::Texture highScores;
    static sf::Texture boberStand;
    static sf::Texture boberCrouch;
    static sf::Texture boberJump;
    static sf::Texture boberFlip;
    static sf::Texture boberSlide;
    static sf::Texture box;
    static sf::Texture rail;
    static sf::Texture pipe;
    static sf::Texture grid;
    static sf::Texture gridStick;
    static sf::Texture heart;
    static sf::Texture boxBroken;
    static sf::Texture gridBroken;

    TexturesManager();
};

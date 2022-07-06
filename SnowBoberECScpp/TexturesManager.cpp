#include "TexturesManager.h"

sf::Texture TexturesManager::background;
sf::Texture TexturesManager::start;
sf::Texture TexturesManager::gameOver;
sf::Texture TexturesManager::highScores;
sf::Texture TexturesManager::boberStand;
sf::Texture TexturesManager::boberCrouch;
sf::Texture TexturesManager::boberJump;
sf::Texture TexturesManager::boberFlip;
sf::Texture TexturesManager::boberSlide;
sf::Texture TexturesManager::box;
sf::Texture TexturesManager::rail;
sf::Texture TexturesManager::pipe;
sf::Texture TexturesManager::grid;
sf::Texture TexturesManager::gridStick;
sf::Texture TexturesManager::heart;
sf::Texture TexturesManager::boxBroken;
sf::Texture TexturesManager::gridBroken;

TexturesManager::TexturesManager() {
    background.loadFromFile("assets/background.jpg");
    start.loadFromFile("assets/start.jpg");
    gameOver.loadFromFile("assets/game-over.jpg");
    highScores.loadFromFile("assets/high-scores.jpg");
    boberStand.loadFromFile("assets/bober-stand.png");
    boberCrouch.loadFromFile("assets/bober-luzny.png");
    boberJump.loadFromFile("assets/bober-jump.png");
    boberFlip.loadFromFile("assets/bober-flip.png");
    boberSlide.loadFromFile("assets/bober-rail.png");
    box.loadFromFile("assets/box.png");
    rail.loadFromFile("assets/rail.png");
    pipe.loadFromFile("assets/grubas.png");
    grid.loadFromFile("assets/grid.png");
    gridStick.loadFromFile("assets/grid-stick.png");
    heart.loadFromFile("assets/heart.png");
    boxBroken.loadFromFile("assets/box-broken.png");
    gridBroken.loadFromFile("assets/grid-broken.png");
}

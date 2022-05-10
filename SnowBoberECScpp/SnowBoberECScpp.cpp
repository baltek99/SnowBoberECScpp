#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "TexturesManager.h"

int main()
{
    Game snowBoberGame;

    TexturesManager texturesManager;

    snowBoberGame.gameLoop();

    return 0;
}

#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "World.h"
#include "TexturesManager.h"

class Game
{
public:
    using Entity = unsigned int;

	sf::RenderWindow window;
	sf::View view;

    World mainMenuECS;
    World gameplayECS;
    World gameOverECS;
    World highScoresECS;

    TexturesManager texturesManager;

	long gameFrame;
    float deltaTime;
	GameState gameState;

	Game();

    void createGameWorld(std::string playerName);

    void createGameOverWorld();

    void createMainMenuWorld();

    void createHighScoreWorld();

    void gameLoop();

    GameState updateState(GameState state, long frame, float delta);

    void resizeView(sf::RenderWindow& window_, sf::View& view_);
};


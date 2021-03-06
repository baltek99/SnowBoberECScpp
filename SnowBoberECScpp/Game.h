#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "World.h"
#include "TexturesManager.h"
#include "InputManager.h"
#include "HighScores.h"

class Game
{
public:
    using Entity = unsigned int;

	sf::RenderWindow window;
	sf::View view;
    sf::Font boxFont;
    sf::Music gameMusic;

    World mainMenuECS;
    World gameplayECS;
    World gameOverECS;
    World highScoresECS;

    TexturesManager texturesManager;
    InputManager inputManager;

    HighScores highScores;
    GameState gameState;
    bool gameOver;
	long gameFrame;
    float deltaTime;
    int result;
    std::string playerName;
    int playerResult;

	Game();

    void updateWorld();

    void renderWorld();

    void createGameWorld(std::string playerName, const sf::Event& event_);

    void createGameOverWorld();

    void createMainMenuWorld();

    void createHighScoreWorld();

    void gameLoop();

    void resizeView(sf::RenderWindow& window_, sf::View& view_);
};

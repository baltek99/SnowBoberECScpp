#include "Game.h"
#include "ConstValues.h"
#include "RenderSystem.h"
#include "TexturesManager.h"

Game::Game() {
    window.create(sf::VideoMode(unsigned int(ConstValues::V_WIDTH), unsigned int(ConstValues::V_HEIGHT)), "SnowBober");
    view = sf::View(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), sf::Vector2f(ConstValues::V_WIDTH, ConstValues::V_HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    srand(unsigned int(time(0)));
    gameFrame = 0;
    gameState = GameState::MAIN_MENU;

    mainMenuECS.fillWorld();
    highScoresECS.fillWorld();
    gameplayECS.fillWorld();
    gameOverECS.fillWorld();

    createMainMenuWorld();
}

void Game::gameLoop() {
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                break;
            }
        }

        window.clear();
        window.setView(view);

        gameFrame++;

        mainMenuECS.updateRenderSystems(gameFrame, deltaTime);

        window.display();
    }
}

void Game::createMainMenuWorld() { 
    mainMenuECS.addRenderSystem(std::make_unique<RenderSystem>(window));

    Entity background = 0;
    sf::Vector2u size = texturesManager.start.getSize();
    float skalaX = ConstValues::V_WIDTH / float(size.x);
    float skalaY = ConstValues::V_HEIGHT / float(size.y);

    printf("dane %u %u \n" , size.x, size.y);
    mainMenuECS.addComponentToEntity<Visual>(background, Visual(texturesManager.start, skalaX, skalaY));
    mainMenuECS.addComponentToEntity<Position>(background, Position(0, 0));
}

void Game::createGameWorld(std::string playerName) {}

void Game::createGameOverWorld() {}

void Game::createHighScoreWorld() {}

GameState Game::updateState(GameState state, long frame, float delta) {}

void Game::resizeView(sf::RenderWindow& window_, sf::View& view_) {
    float wx = float(window_.getSize().x);
    float wy = float(window_.getSize().y);
    float aspectRatio = wx / wy;
    float originalRatio = float(ConstValues::V_WIDTH) / float(ConstValues::V_HEIGHT);

    if (aspectRatio > originalRatio) {
        float heightRatio = wy / float(ConstValues::V_HEIGHT);
        float expectedWidth = float(ConstValues::V_WIDTH) * heightRatio;
        float widthDiff = wx - expectedWidth;

        view_.setViewport(sf::FloatRect((widthDiff / 4.f) / wx, 0.f, (1.f - (widthDiff / 2.f) / wx), 1.f));
    }
    else if (aspectRatio < originalRatio) {
        float widthRatio = wx / float(ConstValues::V_WIDTH);
        float expectedHeight = float(ConstValues::V_HEIGHT) * widthRatio;
        float heightDiff = wy - expectedHeight;

        view_.setViewport(sf::FloatRect(0.f, (heightDiff / 4.f) / wy, 1.f, 1.f - (heightDiff / 2.f) / wy));
    }
}

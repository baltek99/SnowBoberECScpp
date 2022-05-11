#include "Game.h"
#include "ConstValues.h"
#include "RenderSystem.h"
#include <chrono>
#include "InputManager.h"
#include "MoveSystem.h"
#include "BackgroundGeneratorSystem.h"
#include "ObstacleGeneratorSystem.h"
#include "PlayerControlledSystem.h"
#include "CollisionSystem.h"
#include "JumpSystem.h"
#include "SpeedSystem.h"
#include "ImmortalSystem.h"
#include "PlayerCollisionSystem.h"
#include "GameOverSystem.h"
#include "RailSystem.h"
#include "ScoreRenderSystem.h"
#include "ResultRenderSystem.h"

Game::Game() {
    window.create(sf::VideoMode(unsigned int(ConstValues::V_WIDTH), unsigned int(ConstValues::V_HEIGHT)), "SnowBober");
    view = sf::View(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f), sf::Vector2f(ConstValues::V_WIDTH, ConstValues::V_HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    srand(unsigned int(time(0)));
    gameFrame = 0;
    gameOver = false;
    gameState = GameState::MAIN_MENU;

    mainMenuECS.fillWorld();
    highScoresECS.fillWorld();
    gameplayECS.fillWorld();
    gameOverECS.fillWorld();

    createMainMenuWorld();
    playerName = "Bober";
}

void Game::gameLoop() {
    int fps = 100;
    std::chrono::milliseconds timestep = std::chrono::milliseconds(1000 / fps);
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            inputManager.update(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                break;
            case sf::Event::TextEntered:
                if (gameState == GameState::MAIN_MENU) {
                    //textBox.typedOn(event);
                }
            case sf::Event::KeyPressed:
                if (gameState == GameState::GAMEPLAY) {
                    
                }
                else if (gameState == GameState::MAIN_MENU || gameState == GameState::GAME_OVER) {
                    if (event.key.code == sf::Keyboard::Tab) {
                        gameState = GameState::HIGH_SCORES;
                        createHighScoreWorld();
                    }
                    else if ((gameState == GameState::MAIN_MENU && event.key.code == sf::Keyboard::Enter) || gameState == GameState::GAME_OVER) {
                        gameState = GameState::GAMEPLAY;
                        createGameWorld(playerName, event);
                    }
                }
                else if (gameState == GameState::HIGH_SCORES) {
                    if (event.key.code == sf::Keyboard::Tab) {
                        gameState = GameState::MAIN_MENU;
                        createMainMenuWorld();
                    }
                }
                break;
            }
        }

        window.clear();
        window.setView(view);

        std::chrono::milliseconds current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

        if (current_ms > ms + timestep) {
            gameFrame++;
            updateWorld();
            inputManager.update();
            ms = current_ms;
        }

        renderWorld();

        window.display();
    }
}

void Game::updateWorld() {
    if (gameState == GameState::MAIN_MENU) {
        mainMenuECS.updateSystems(gameFrame, deltaTime);
    }
    else if (gameState == GameState::GAMEPLAY) {
        if (gameOver) {
            gameState = GameState::GAME_OVER;
            createGameOverWorld();
            return;
        }
        gameplayECS.updateSystems(gameFrame, deltaTime);
    }
    else if (gameState == GameState::GAME_OVER) {
        gameOverECS.updateSystems(gameFrame, deltaTime);
    }
}

void Game::renderWorld() {
    switch (gameState) {
    case GameState::HIGH_SCORES: highScoresECS.updateRenderSystems(gameFrame, deltaTime); break;
    case GameState::MAIN_MENU: mainMenuECS.updateRenderSystems(gameFrame, deltaTime); break;
    case GameState::GAMEPLAY: gameplayECS.updateRenderSystems(gameFrame, deltaTime); break;
    case GameState::GAME_OVER: gameOverECS.updateRenderSystems(gameFrame, deltaTime); break;
    }
}

void Game::createMainMenuWorld() { 
    mainMenuECS.resetWorld();
    gameFrame = 0;

    mainMenuECS.addRenderSystem(std::make_unique<RenderSystem>(window));

    Entity background = 0;
    sf::Vector2u size = texturesManager.start.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    mainMenuECS.addComponentToEntity<Visual>(background, Visual(texturesManager.start, scaleX, scaleY));
    mainMenuECS.addComponentToEntity<Position>(background, Position(0, 0));
}

void Game::createGameWorld(std::string playerName, const sf::Event& event_) {
    gameplayECS.resetWorld();

    gameFrame = 0;
    gameOver = false;

    gameplayECS.addSystem(std::make_unique<MoveSystem>());
    gameplayECS.addSystem(std::make_unique<BackgroundGeneratorSystem>());
    gameplayECS.addSystem(std::make_unique<ObstacleGeneratorSystem>(3, 12, 7, 4, &texturesManager));
    gameplayECS.addSystem(std::make_unique<PlayerControlledSystem>(event_, &texturesManager, &inputManager));
    gameplayECS.addSystem(std::make_unique<CollisionSystem>());
    gameplayECS.addSystem(std::make_unique<PlayerCollisionSystem>(&texturesManager, this));
    gameplayECS.addSystem(std::make_unique<JumpSystem>(&texturesManager));
    gameplayECS.addSystem(std::make_unique<RailSystem>(&texturesManager));
    gameplayECS.addSystem(std::make_unique<SpeedSystem>());
    gameplayECS.addSystem(std::make_unique<ImmortalSystem>());
    gameplayECS.addSystem(std::make_unique<GameOverSystem>(this));

    gameplayECS.addRenderSystem(std::make_unique<RenderSystem>(window));
    gameplayECS.addRenderSystem(std::make_unique<ScoreRenderSystem>(window));

    Entity background1 = 0;
    sf::Vector2u size = texturesManager.background.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    gameplayECS.addComponentToEntity<Visual>(background1, Visual(texturesManager.background, scaleX, scaleY));
    gameplayECS.addComponentToEntity<Position>(background1, Position(0, 0));
    gameplayECS.addComponentToEntity<Move>(background1, Move(-2)); 
    
    Entity background2 = 1;
    gameplayECS.addComponentToEntity<Visual>(background2, Visual(texturesManager.background, scaleX, scaleY));
    gameplayECS.addComponentToEntity<Position>(background2, Position(ConstValues::V_WIDTH, 0));
    gameplayECS.addComponentToEntity<Move>(background2, Move(-2));

    Entity life1 = 16;
    gameplayECS.addComponentToEntity(life1, Position(ConstValues::HEART_POSITION_X_1, ConstValues::HEART_POSITION_Y));
    gameplayECS.addComponentToEntity(life1, Visual(texturesManager.heart, ConstValues::HEART_WIDTH, ConstValues::HEART_HEIGHT));

    Entity life2 = 17;
    gameplayECS.addComponentToEntity(life2, Position(ConstValues::HEART_POSITION_X_2, ConstValues::HEART_POSITION_Y));
    gameplayECS.addComponentToEntity(life2, Visual(texturesManager.heart, ConstValues::HEART_WIDTH, ConstValues::HEART_HEIGHT));

    Entity life3 = 18;
    gameplayECS.addComponentToEntity(life3, Position(ConstValues::HEART_POSITION_X_3, ConstValues::HEART_POSITION_Y));
    gameplayECS.addComponentToEntity(life3, Visual(texturesManager.heart, ConstValues::HEART_WIDTH, ConstValues::HEART_HEIGHT));

    std::vector<std::optional<int>> lives;
    lives.push_back(std::optional<int>(16));
    lives.push_back(std::optional<int>(17));
    lives.push_back(std::optional<int>(18));

    Entity player = 11;
    gameplayECS.addComponentToEntity<Visual>(player, Visual(texturesManager.boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
    gameplayECS.addComponentToEntity<Position>(player, Position(ConstValues::BOBER_DEFAULT_POSITION_X, ConstValues::BOBER_DEFAULT_POSITION_Y));
    gameplayECS.addComponentToEntity<Jump>(player, Jump());
    gameplayECS.addComponentToEntity<PlayerControlled>(player, PlayerControlled(PlayerState::IDLE, playerName));
    gameplayECS.addComponentToEntity<Collision>(player, Collision(ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT, ObstacleType::PLAYER));
    gameplayECS.addComponentToEntity<Score>(player, Score(0));
    gameplayECS.addComponentToEntity<Lives>(player, Lives(lives));

    Entity scoreLabel = 2;
    gameplayECS.addComponentToEntity<Position>(scoreLabel, Position(ConstValues::SCORE_POSITION_X, ConstValues::SCORE_POSITION_Y));
    gameplayECS.addComponentToEntity<ScoreBind>(scoreLabel, ScoreBind(player));

}

void Game::createGameOverWorld() {
    gameOverECS.resetWorld();
    gameFrame = 0;

    gameOverECS.addRenderSystem(std::make_unique<RenderSystem>(window));
    gameOverECS.addRenderSystem(std::make_unique<ResultRenderSystem>(window));

    Entity background = 0;
    sf::Vector2u size = texturesManager.gameOver.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    gameOverECS.addComponentToEntity<Visual>(background, Visual(texturesManager.gameOver, scaleX, scaleY));
    gameOverECS.addComponentToEntity<Position>(background, Position(0, 0));

    Entity result = 1;
    gameOverECS.addComponentToEntity<TextField>(result, TextField(playerName));
    gameOverECS.addComponentToEntity<Score>(result, Score(playerResult));
    gameOverECS.addComponentToEntity<Position>(result, Position(300, 500));
}

void Game::createHighScoreWorld() {}

GameState Game::updateState(GameState state, long frame, float delta) {
    return GameState::GAMEPLAY;
}

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

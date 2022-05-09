#include "GameOverSystem.h"
#include "World.h"
#include "Game.h"

GameOverSystem::GameOverSystem(Game* game_) : game(game_) {
    pcExist = true;
}

void GameOverSystem::update(long gameFrame, float delta, World* world) {

    pcExist = false;
    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<PlayerControlled>(entity)) {
            continue;
        }

        pcExist = true;
    }

    if (!pcExist) {
        printf("Game over \n"); 
        game->gameOver = true;
    }
}

#include "SpeedSystem.h"
#include "World.h"
#include "ConstValues.h"

void SpeedSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Move>& movVec = world->getComponents<Move>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Move>(entity)) {
            continue;
        } 
        if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
            Move& mov = movVec.at(entity).value();
            mov.speed--;
        }
    }
}
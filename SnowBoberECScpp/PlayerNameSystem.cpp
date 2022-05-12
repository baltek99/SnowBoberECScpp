#include "PlayerNameSystem.h"
#include "World.h"

void PlayerNameSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<TextField>& fieldVec = world->getComponents<TextField>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, TextField>(entity)) {
            continue;
        }
    }
}

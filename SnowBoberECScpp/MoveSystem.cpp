#include "MoveSystem.h"
#include "World.h"

void MoveSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Move>& visVec = world->getComponents<Move>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, Move>(entity)) {
            continue;
        };

        Position& pos = posVec.at(entity).value();
        Move& mov = visVec.at(entity).value();

        pos.x += mov.speed;
    }
}

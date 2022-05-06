#include "MoveSystem.h"
#include "World.h"

void MoveSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Move>& visVec = world->getComponents<Move>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, Move>(entity)) {
            continue;
        }

        //std::optional<Position>& opt_pos = posVec.at(entity);
        //std::optional<Visual>& opt_vis = vis.at(entity);

        Position& pos = posVec.at(entity).value();
        Move& mov = visVec.at(entity).value();

        printf("%i \n", pos.x);
        pos.x += mov.speed;
    }
}
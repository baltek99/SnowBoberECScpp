#include "BackgroundGeneratorSystem.h"
#include "World.h"
#include "ConstValues.h"

void BackgroundGeneratorSystem::update(long gameFrame, float delta, World* world) {
    
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Move>& movVec = world->getComponents<Move>();

    for (int entity = 0; entity < 2; entity++) {
        if (!world->isEntityOk<Position, Move>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        
        if (pos.x <= -ConstValues::V_WIDTH) {
            pos.x = ConstValues::V_WIDTH + pos.x % int(ConstValues::V_WIDTH);
        }
    }
}

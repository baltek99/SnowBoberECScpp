#include "RailSystem.h"
#include "World.h"
#include "ConstValues.h"
#include "TexturesManager.h"

RailSystem::RailSystem(const TexturesManager* texManager) : textures(texManager) {}

void RailSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<CollisionResponse>& crVec = world->getComponents<CollisionResponse>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<PlayerControlled>& pcVec = world->getComponents<PlayerControlled>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<PlayerControlled, Visual, Position, CollisionResponse>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        CollisionResponse& cr = crVec.at(entity).value();
        PlayerControlled& pc = pcVec.at(entity).value();
        Visual& vis = visVec.at(entity).value();
        
        if (!world->getComponent<Position>(cr.collidingEntityId).has_value()) continue;
        int obstacleX = world->getComponent<Position>(cr.collidingEntityId).value().x;
        int playerX = pos.x;

        if (pc.playerState == PlayerState::SLIDING && obstacleX < playerX && std::abs(playerX - obstacleX) >= ConstValues::RAIL_AND_BOBER_DIFFERENCE) {
            world->removeComponentFromEntity<CollisionResponse>(cr.collidingEntityId);
            world->removeComponentFromEntity<CollisionResponse>(entity);
            pc.playerState = PlayerState::IDLE;
            pos.y = ConstValues::IDLE_RIDE_Y;
            world->addComponentToEntity(entity, Visual(textures->boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
        }
    }
}

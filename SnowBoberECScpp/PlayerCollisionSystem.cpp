#include "PlayerCollisionSystem.h"
#include "World.h"
#include "ConstValues.h"
#include "TexturesManager.h"
#include "Game.h"

PlayerCollisionSystem::PlayerCollisionSystem(const TexturesManager* texManager, Game* game_) : textures(texManager), game(game_) {
}

void PlayerCollisionSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<PlayerControlled>& pcVec = world->getComponents<PlayerControlled>();
    World::OptVec<CollisionResponse>& crVec = world->getComponents<CollisionResponse>();
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();
    World::OptVec<Score>& scoreVec = world->getComponents<Score>();
    World::OptVec<Lives>& livVec = world->getComponents<Lives>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<CollisionResponse, PlayerControlled, Position, Visual, Score, Lives>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        CollisionResponse& cr = crVec.at(entity).value();
        PlayerControlled& pc = pcVec.at(entity).value();
        Visual& vis = visVec.at(entity).value();
        Score& score = scoreVec.at(entity).value();
        Lives& liv = livVec.at(entity).value();

        if (cr.obstacle == ObstacleType::SCORE_POINT) {
            score.score++;
            world->killEntity(cr.collidingEntityId);
            world->removeComponentFromEntity<CollisionResponse>(entity);
        }
        else if (cr.obstacle == ObstacleType::BOX || (cr.obstacle == ObstacleType::RAIL && (pc.playerState == PlayerState::IDLE || pc.playerState == PlayerState::CROUCH))) {
            removeLifeOrKill(world, entity, liv, score.score, cr.collidingEntityId);
            pos.y = ConstValues::BOBER_DEFAULT_POSITION_Y;
            world->addComponentToEntity<Visual>(entity, Visual(textures->boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
            if (cr.obstacle == ObstacleType::BOX) {
                world->addComponentToEntity<Visual>(cr.collidingEntityId, Visual(textures->boxBroken, ConstValues::BOX_WIDTH, ConstValues::BOX_HEIGHT));
            }
        }
        else if (cr.obstacle == ObstacleType::RAIL && (pc.playerState == PlayerState::JUMPING || pc.playerState == PlayerState::JUMPING_FROM_CROUCH || pc.playerState == PlayerState::JUMPING_ON_RAIL)) {
            pos.y = ConstValues::SLIDING_ON_RAIL_Y;
            pc.playerState = PlayerState::SLIDING;
            world->addComponentToEntity<Visual>(entity, Visual(textures->boberSlide, ConstValues::BOBER_ON_RAIL_WIDTH, ConstValues::BOBER_ON_RAIL_HEIGHT));
            world->removeComponentFromEntity<Collision>(cr.collidingEntityId);
        }
        else if (cr.obstacle == ObstacleType::GRID) {
            if (pc.playerState != PlayerState::CROUCH) {
                removeLifeOrKill(world, entity, liv, score.score, cr.collidingEntityId);
                pos.y = ConstValues::BOBER_DEFAULT_POSITION_Y;
                world->addComponentToEntity<Visual>(cr.collidingEntityId - 9, Visual(textures->gridBroken, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT));
                world->killEntity(cr.collidingEntityId);
            }
            else {
                world->removeComponentFromEntity<CollisionResponse>(entity);
            }
        }
    }
}

void PlayerCollisionSystem::removeLifeOrKill(World* world, int entity, Lives& liv, int score, int obstacleId) {
    int lifeID = liv.livesIds.at(0).value();
    if (liv.livesIds.size() == 1) {
        game->playerResult = score;
        world->killEntity(entity);
        world->killEntity(lifeID);
    }
    else {
        liv.livesIds.erase(liv.livesIds.begin());
        world->killEntity(lifeID);
        world->removeComponentFromEntity<Collision>(entity);
        world->removeComponentFromEntity<CollisionResponse>(entity);
        world->removeComponentFromEntity<Collision>(obstacleId);
    }
}

#include "JumpSystem.h"
#include "World.h"
#include "ConstValues.h"
#include "TexturesManager.h"
#include "Util.h"

JumpSystem::JumpSystem(const TexturesManager* texturesManager) : textures(texturesManager) {
    jumpHeight = 120;
    duration = 110;
    rotationSpeed = 3.3f;
    ollieUpSpeed = -1.2f;
    ollieDownSpeed = 0.4f;
    speedCount = 5;
    frame = 0;
}

void JumpSystem::update(long gameFrame, float delta, World* world) {
    frame++;
    
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<PlayerControlled>& pcVec = world->getComponents<PlayerControlled>();
    World::OptVec<Jump>& jumpVec = world->getComponents<Jump>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();

    //if (gameFrame == ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
    //    jumpHeight = 110;
    //    duration = 80;
    //    rotationSpeed = 4.5f;
    //}
    //else if (gameFrame == 5 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
    //    duration = 70;
    //    rotationSpeed = 5.5f;
    //}
    //else if (gameFrame == 6 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
    //    duration = 65;
    //    rotationSpeed = 6.f;
    //}
    //else if (gameFrame == 8 * ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
    if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        duration = duration - duration / speedCount;
        rotationSpeed = rotationSpeed + rotationSpeed / speedCount;
        ollieUpSpeed = ollieUpSpeed + ollieUpSpeed / speedCount;
        ollieDownSpeed = ollieDownSpeed + ollieDownSpeed / speedCount;
        speedCount++;
    }

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<PlayerControlled, Position, Jump, Visual>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        PlayerControlled& pctrl = pcVec.at(entity).value();
        Jump& jump = jumpVec.at(entity).value();
        Visual& vis = visVec.at(entity).value();

        if (pctrl.playerState == PlayerState::JUMPING || pctrl.playerState == PlayerState::JUMPING_ON_RAIL
            || pctrl.playerState == PlayerState::JUMPING_FROM_CROUCH) {

            if (gameFrame >= jump.startJumpFrame + duration) {
                pctrl.playerState = PlayerState::IDLE;
                pos.y = ConstValues::IDLE_RIDE_Y;
                vis.sprite.setRotation(0);
                world->addComponentToEntity<Visual>(entity, Visual(textures->boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));  
            }
            else {
                pos.y = (int)Util::lerp(
                    jump.jumpFrom,
                    jump.jumpFrom - jumpHeight,
                    Util::spike((gameFrame - jump.startJumpFrame) / duration)
                );

                if (pctrl.playerState == PlayerState::JUMPING_ON_RAIL) {                  
                    vis.sprite.rotate(rotationSpeed);
                }
                else if (pctrl.playerState == PlayerState::JUMPING_FROM_CROUCH) {
                    vis.sprite.rotate(-rotationSpeed);
                }
                else {
                    if ((gameFrame - jump.startJumpFrame) / duration < 0.15f)
                       vis.sprite.rotate(ollieUpSpeed);

                    else if (vis.sprite.getRotation() > -10)
                        vis.sprite.rotate(ollieDownSpeed);
                }
            }
        }
    }
}

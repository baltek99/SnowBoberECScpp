#include "PlayerControlledSystem.h"
#include "World.h"
#include "PlayerControlled.h"
#include "Jump.h"
#include "Visual.h"
#include "ConstValues.h"
#include "TexturesManager.h"
#include "InputManager.h"

PlayerControlledSystem::PlayerControlledSystem(const sf::Event& event, const TexturesManager* texturesManager, InputManager* inputManager_) : actualEvent(event), textures(texturesManager) {    
    inputManager = inputManager_;
}

void PlayerControlledSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<PlayerControlled>& pcVec = world->getComponents<PlayerControlled>();
    World::OptVec<Jump>& jumpVec = world->getComponents<Jump>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<PlayerControlled, Position, Visual, Jump>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        PlayerControlled& pctrl = pcVec.at(entity).value();
        Jump& jump = jumpVec.at(entity).value();
        Visual& vis = visVec.at(entity).value();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && pctrl.playerState == PlayerState::IDLE) {
            pos.x = pos.x + 5;
            if (pos.x > ConstValues::BOBER_MAX_X) pos.x = ConstValues::BOBER_MAX_X;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && pctrl.playerState == PlayerState::IDLE) {
            pos.x = pos.x - 5;
            if (pos.x < ConstValues::BOBER_MIN_X) pos.x = ConstValues::BOBER_MIN_X;
        }

        if (inputManager->isKeyJustPressed(sf::Keyboard::Space)) {
            if (pctrl.playerState == PlayerState::SLIDING) {
                pctrl.playerState = PlayerState::JUMPING_ON_RAIL;
                jump.jumpFrom = ConstValues::JUMP_FROM_RAIL_Y;
                jump.startJumpFrame = gameFrame;
                world->addComponentToEntity<Visual>(entity, Visual(textures->boberFlip, ConstValues::BOBER_IN_JUMP_WIDTH, ConstValues::BOBER_IN_JUMP_HEIGHT));
                world->removeComponentFromEntity<CollisionResponse>(entity);
            }
            else if (pctrl.playerState == PlayerState::IDLE || pctrl.playerState == PlayerState::CROUCH) {
                if (pctrl.playerState == PlayerState::CROUCH) {
                    pctrl.playerState = PlayerState::JUMPING_FROM_CROUCH;
                    world->addComponentToEntity<Visual>(entity, Visual(textures->boberFlip, ConstValues::BOBER_IN_JUMP_WIDTH, ConstValues::BOBER_IN_JUMP_HEIGHT));
                }
                else {
                    pctrl.playerState = PlayerState::JUMPING;
                    world->addComponentToEntity<Visual>(entity, Visual(textures->boberJump, ConstValues::BOBER_IN_JUMP_WIDTH, ConstValues::BOBER_IN_JUMP_HEIGHT));
                }
                jump.jumpFrom = ConstValues::JUMP_FROM_GROUND_Y;
                jump.startJumpFrame = gameFrame;
            }
        }
        else if (inputManager->isKeyJustPressed(sf::Keyboard::LControl)) {
            if (pctrl.playerState == PlayerState::IDLE) {
                pctrl.playerState = PlayerState::CROUCH;
                pos.y = ConstValues::BOBER_CROUCH_POSITION_Y;
                world->addComponentToEntity<Visual>(entity, Visual(textures->boberCrouch, ConstValues::BOBER_CROUCH_WIDTH, ConstValues::BOBER_CROUCH_HEIGHT));
            }
            else if (pctrl.playerState == PlayerState::CROUCH) {
                pctrl.playerState = PlayerState::IDLE;
                pos.y = ConstValues::IDLE_RIDE_Y;
                world->addComponentToEntity<Visual>(entity, Visual(textures->boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
            }
        }

    }
}

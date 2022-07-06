#include "TextBoxInputSystem.h"
#include "World.h"
#include "InputManager.h"
#include "Game.h"

TextBoxInputSystem::TextBoxInputSystem(InputManager* manager, Game* game_) : inputManager(manager), game(game_) {
}

void TextBoxInputSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<TextField>& fieldVec = world->getComponents<TextField>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<TextField>(entity)) {
            continue;
        }

        TextField& field = fieldVec.at(entity).value();

        while (inputManager->charsTyped.size() > 0) {
            field.textBox.typedOn(inputManager->charsTyped.front());
            inputManager->charsTyped.pop();
        }
        game->playerName = field.textBox.getText();
    }
}

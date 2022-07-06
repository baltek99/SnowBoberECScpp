#include "TextBoxRenderSystem.h"
#include "World.h"

TextBoxRenderSystem::TextBoxRenderSystem(sf::RenderWindow& win) : window(win) {
}

void TextBoxRenderSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<TextField>& fieldVec = world->getComponents<TextField>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, TextField>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        TextField& field = fieldVec.at(entity).value();

        field.textBox.setPosition({ float(pos.x), float(pos.y) });
        field.textBox.draw(window);
    }
}

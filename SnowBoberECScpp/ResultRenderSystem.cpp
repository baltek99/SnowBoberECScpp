#include "ResultRenderSystem.h"
#include "World.h"
#include "ConstValues.h"

ResultRenderSystem::ResultRenderSystem(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/cour.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
}

void ResultRenderSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Score>& scoreVec = world->getComponents<Score>();
    World::OptVec<TextField>& textVec = world->getComponents<TextField>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, Score, TextField>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        Score& score = scoreVec.at(entity).value();
        TextField& textField = textVec.at(entity).value();       

        text.setString("Player: " + textField.text + "    Score: " + std::to_string(score.score));
        text.setPosition(pos.x, pos.y);
        window.draw(text);
    }
}

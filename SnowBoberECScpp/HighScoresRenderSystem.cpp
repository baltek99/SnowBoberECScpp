#include "HighScoresRenderSystem.h"
#include "World.h"

HighScoresRenderSystem::HighScoresRenderSystem(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/cour.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
}

void HighScoresRenderSystem::update(long gameFrame, float delta, World* world) {

    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<ResultBind>& bindVec = world->getComponents<ResultBind>();
    World::OptVec<Score>& scoreVec = world->getComponents<Score>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, ResultBind, Score>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        Score& score = scoreVec.at(entity).value();
        ResultBind& bind = bindVec.at(entity).value();

        std::string row = std::to_string(score.score) + ". " + bind.name + " : " + std::to_string(bind.score);

        text.setString(row);
        text.setPosition(pos.x, pos.y);
        window.draw(text);
    }
}


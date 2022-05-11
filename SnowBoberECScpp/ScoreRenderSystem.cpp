#include "ScoreRenderSystem.h"
#include "World.h"
#include "ConstValues.h"

ScoreRenderSystem::ScoreRenderSystem(sf::RenderWindow& win) : window(win) {
    font.loadFromFile("assets/cour.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
}

void ScoreRenderSystem::update(long gameFrame, float delta, World* world) {

    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<ScoreBind>& sbVec = world->getComponents<ScoreBind>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<Position, ScoreBind>(entity)) {
            continue;
        }

        Position& pos = posVec.at(entity).value();
        ScoreBind& sb = sbVec.at(entity).value();

        std::optional<Score>& scoreOpt = world->getComponent<Score>(sb.playerId);

        if (!scoreOpt.has_value()) continue;

        text.setString("Score: " + std::to_string(scoreOpt.value().score));
        text.setPosition(pos.x, pos.y);
        window.draw(text);
    }
}

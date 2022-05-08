#include "RenderSystem.h"
#include "World.h"

RenderSystem::RenderSystem(sf::RenderWindow& win) : window(win) {

}

void RenderSystem::update(long gameFrame, float delta, World* world) {
     World::OptVec<Position>& posVec = world->getComponents<Position>();
     World::OptVec<Visual>& visVec = world->getComponents<Visual>();

     for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
         if (!world->isEntityOk<Position, Visual>(entity)) {
             continue;
         }

         //std::optional<Position>& opt_pos = pos.at(entity);
         //std::optional<Visual>& opt_vis = vis.at(entity);

         Position& pos = posVec.at(entity).value();
         Visual& vis = visVec.at(entity).value();

         vis.sprite.setPosition(pos.x + vis.sprite.getScale().x * vis.sprite.getLocalBounds().width / 2, 
             pos.y + vis.sprite.getScale().y * vis.sprite.getLocalBounds().height / 2);

         window.draw(vis.sprite);
     }
}
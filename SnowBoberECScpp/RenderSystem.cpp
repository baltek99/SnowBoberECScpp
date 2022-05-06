#include "RenderSystem.h"
#include "World.h"

RenderSystem::RenderSystem(sf::RenderWindow& win) : window(win) {

}

void RenderSystem::update(long gameFrame, float delta, World* world) {
     World::OptVec<Position> pos =  world->getComponents<Position>();
     World::OptVec<Visual> vis =  world->getComponents<Visual>();

     for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
         if (!world->isEntityOk<Position, Visual>(entity)) {
             continue;
         }

         //std::optional<Position>& opt_pos = pos.at(entity);
         //std::optional<Visual>& opt_vis = vis.at(entity);

         Position& p = pos.at(entity).value();
         Visual& v = vis.at(entity).value();

         v.sprite.setPosition(p.x + v.sprite.getScale().x * v.sprite.getLocalBounds().width / 2, 
             p.y + v.sprite.getScale().y * v.sprite.getLocalBounds().height / 2);

         window.draw(v.sprite);
     }
}
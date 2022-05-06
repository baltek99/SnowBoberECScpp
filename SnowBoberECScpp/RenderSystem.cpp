#include "RenderSystem.h"
#include "World.h"

RenderSystem::RenderSystem(sf::RenderWindow& win) : window(win) {

}

void RenderSystem::update(long gameFrame, float delta, World* world) {
     World::OptVec<Position> pos =  world->getComponents<Position>();
     World::OptVec<Visual> vis =  world->getComponents<Visual>();

     for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
         std::optional<Position>& opt_pos = pos.at(entity);
         std::optional<Visual>& opt_vis = vis.at(entity);
         if (!opt_pos.has_value() || !opt_vis.has_value()) {
             continue;
         }
         Position& p = opt_pos.value();
         Visual& v = opt_vis.value();

         v.sprite.setPosition(p.x + v.sprite.getScale().x * v.sprite.getLocalBounds().width / 2, 
             p.y + v.sprite.getScale().y * v.sprite.getLocalBounds().height / 2);

         window.draw(v.sprite);
     }
}
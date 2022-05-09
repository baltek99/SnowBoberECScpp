#include "ImmortalSystem.h"
#include "World.h"
#include "ConstValues.h"

ImmortalSystem::ImmortalSystem() {
	initialImmortalDurationVal = 150;
	immortalDuration = 150;
}

void ImmortalSystem::update(long gameFrame, float delta, World* world) {

    World::OptVec<Collision>& colVec = world->getComponents<Collision>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();

    for (unsigned int entity = 0; entity < world->MAX_ENTITIES; entity++) {
        if (!world->isEntityOk<PlayerControlled, Visual>(entity)) {
            continue;
        }

        std::optional<Collision>& colOpt = colVec.at(entity);
        Visual& vis = visVec.at(entity).value();

        if (gameFrame == ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) {
            if (immortalDuration == initialImmortalDurationVal) {
                immortalDuration = 100;
            }
            initialImmortalDurationVal = 100;
        }

        if (!colOpt.has_value() && immortalDuration > 0) {
            if (immortalDuration % 20 == 0) {
                vis.isVisible = !vis.isVisible;
            }
            immortalDuration--;
        }
        else if (!colOpt.has_value()) {
            immortalDuration = initialImmortalDurationVal;
            world->addComponentToEntity<Collision>(entity, Collision(ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT, ObstacleType::PLAYER));           
            if (!vis.isVisible) {
                vis.isVisible = true;
            }
        }
    }

}

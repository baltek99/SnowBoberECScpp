#include "World.h"

World::World() {
}

void World::resetWorld() {
	removeAllSystems();
	killAllEntities();
}

void World::fillWorld() {
	std::apply([this](auto&& ... args) { (args.resize(MAX_ENTITIES), ...); }, components);
}

void World::addSystem(std::unique_ptr<System>&& system) {
	systems.push_back(std::move(system));
}

void World::addRenderSystem(std::unique_ptr<System>&& system) {
	renderSystems.push_back(std::move(system));
}

void World::removeAllSystems() {
	systems.clear();
	renderSystems.clear();
}

void World::updateSystems(long gameFrame, float delta) {
	std::for_each(systems.begin(), systems.end(), [gameFrame, delta, this](std::unique_ptr<System>& s) {s->update(gameFrame, delta, this);});
}

void World::updateRenderSystems(long gameFrame, float delta) {
	std::for_each(renderSystems.begin(), renderSystems.end(), [gameFrame, delta, this](std::unique_ptr<System>& s) {s->update(gameFrame, delta, this);});
}

void World::killAllEntities() {
	std::apply([this](auto&& ... args) { (clearOptVec(args), ...); }, components);
}

void World::killEntity(unsigned int entityId) {
	std::apply([this, entityId](auto&& ... args) { (clearEntityInOptVec(args, entityId), ...); }, components);
}

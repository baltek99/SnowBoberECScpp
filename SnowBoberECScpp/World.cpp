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

	//std::for_each(anySystems.begin(), anySystems.end(), [gameFrame, delta, this](auto s) { s.update(gameFrame, delta, this); });
}

void World::updateRenderSystems(long gameFrame, float delta) {

}

void World::killAllEntities() {
	//std::apply([this](auto&& ... args) { clearOptVec(args); }, components);
	std::apply([this](auto&& ... args) { (clearOptVec(args), ...); }, components);
}

void World::killEntity(int entityId) {
	//std::apply([this, entityId](auto&& ... args) { clearEntityInOptVec(args, entityId); }, components);
	std::apply([this, entityId](auto&& ... args) { (clearEntityInOptVec(args, entityId), ...); }, components);
}

bool World::isEntityOk(int entityId, const std::vector<std::vector<Component>>& entities) {
	return true;
}
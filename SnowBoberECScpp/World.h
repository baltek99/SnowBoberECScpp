#pragma once

#include <vector>
#include "AllComponents.h"
#include "System.h"
#include <any>

class World
{
public :
    template<class T>
    using OptVec = std::vector<std::optional<T>>;
    using CompsTuple = std::tuple<
        OptVec<Collision>,
        OptVec<CollisionResponse>,
        OptVec<Jump>,
        OptVec<Lives>,
        OptVec<Move>,
        OptVec<PlayerControlled>,
        OptVec<Position>,
        OptVec<ResultBind>,
        OptVec<Score>,
        OptVec<ScoreBind>,
        OptVec<TextField>,
        OptVec<Visual>>;

    const unsigned int MAX_ENTITIES = 20;
    const unsigned int MAX_COMPONENTS = 12;

    std::vector<std::unique_ptr<System>> systems;
    std::vector<std::unique_ptr<System>> renderSystems;

    CompsTuple components;

    World();

    void resetWorld();

    void fillWorld();

    void addSystem(std::unique_ptr<System>&& system);

    void addRenderSystem(std::unique_ptr<System>&& system);

    void removeAllSystems();

    void updateSystems(long gameFrame, float delta);

    void updateRenderSystems(long gameFrame, float delta);

    void killAllEntities();

    void killEntity(unsigned int entityId);

    template<class T>
    void addComponentToEntity(unsigned int entityId, T cmp) {
        OptVec<T>& tComp = std::get<OptVec<T>>(components);
        tComp.at(entityId).emplace(cmp);
    }

    template<class T>
    void removeComponentFromEntity(unsigned int entityId) {
        OptVec<T>& tComp = std::get<OptVec<T>>(components);
        tComp.at(entityId).reset();
    }

    template<class T>
    OptVec<T> getComponents() {
        return std::get<OptVec<T>>(components);
    }

    template<class T>
    std::optional<T> getComponent(unsigned int entityId) {
        return std::get<OptVec<T>>(components).at(entityId);
    }

    static bool isEntityOk(unsigned int entityId, const std::vector<std::vector<Component>>& entities);

private :
    template<class T>
    void clearOptVec(World::OptVec<T>& vec) {
        std::for_each(vec.begin(), vec.end(), [](std::optional<T>& opt) { opt.reset(); });
    }

    template<class T>
    void clearEntityInOptVec(World::OptVec<T>& vec, unsigned int entityId) {
        vec.at(entityId).reset();
    }
};

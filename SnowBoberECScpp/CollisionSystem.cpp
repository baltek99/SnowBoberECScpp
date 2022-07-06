#include "CollisionSystem.h"
#include "World.h"
#include "RotatedRectangle.h"

CollisionSystem::CollisionSystem() {}

void CollisionSystem::update(long gameFrame, float delta, World* world) {
    World::OptVec<Position>& posVec = world->getComponents<Position>();
    World::OptVec<Collision>& colVec = world->getComponents<Collision>();
    World::OptVec<Visual>& visVec = world->getComponents<Visual>();

    for (unsigned int entityA = 0; entityA < world->MAX_ENTITIES; entityA++) {
        if (!world->isEntityOk<Position, Collision, Visual>(entityA)) {
            continue;
        }

        Position& posA = posVec.at(entityA).value();
        Collision& colA = colVec.at(entityA).value();
        Visual& visA = visVec.at(entityA).value();

        for (unsigned int entityB = entityA + 1; entityB < world->MAX_ENTITIES; entityB++) {       
            if (!world->isEntityOk<Position, Collision, Visual>(entityB)) {
                continue;
            }
        
            Position& posB = posVec.at(entityB).value();
            Collision& colB = colVec.at(entityB).value();
            Visual& visB = visVec.at(entityB).value();

            CollisionType type = intersects(posA, colA, visA, posB, colB, visB);
            if (type == CollisionType::NONE) {
                continue;
            }

            world->addComponentToEntity<CollisionResponse>(entityA, CollisionResponse(entityB, type, colB.type));
            world->addComponentToEntity<CollisionResponse>(entityB, CollisionResponse(entityA, type, colA.type));
        }
    }
}

CollisionType CollisionSystem::intersects(const Position& posA, Collision& colA, const Visual& visA, const Position& posB, Collision& colB, const Visual& visB) {

    sf::RectangleShape rshA;
    rshA.setSize(sf::Vector2f(visA.sprite.getLocalBounds().width * visA.sprite.getScale().x,
        visA.sprite.getLocalBounds().height * visA.sprite.getScale().y));
    rshA.setOrigin(rshA.getSize().x / 2, rshA.getSize().y / 2);
    rshA.setRotation(0);
    rshA.setPosition(posA.x + rshA.getSize().x / 2, posA.y + rshA.getSize().y / 2); 
    
    sf::RectangleShape rshB;
    rshB.setSize(sf::Vector2f(visB.sprite.getLocalBounds().width * visB.sprite.getScale().x,
        visB.sprite.getLocalBounds().height * visB.sprite.getScale().y));
    rshB.setOrigin(rshB.getSize().x / 2, rshB.getSize().y / 2);
    rshB.setRotation(0);
    rshB.setPosition(posB.x + rshB.getSize().x / 2, posB.y + rshB.getSize().y / 2);

    colA.rectangle = sf::IntRect(rshA.getGlobalBounds());
    colB.rectangle = sf::IntRect(rshB.getGlobalBounds());

    RotatedRectangle rectA = RotatedRectangle(sf::FloatRect(colA.rectangle), visA.sprite.getRotation());
    RotatedRectangle rectB = RotatedRectangle(sf::FloatRect(colB.rectangle), visB.sprite.getRotation());    

    if (rectA.intersects(rectB)) {
        return CollisionType::INTERSECT;
    }

    return CollisionType::NONE;
}

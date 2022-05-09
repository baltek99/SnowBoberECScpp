#include "CollisionSystem.h"
#include "World.h"

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
    rshA.setTextureRect(sf::IntRect(visA.sprite.getGlobalBounds()));
    rshA.setSize(sf::Vector2f(visA.sprite.getLocalBounds().width * visA.sprite.getScale().x,
        visA.sprite.getLocalBounds().height * visA.sprite.getScale().y));
    rshA.setOrigin(rshA.getSize().x / 2, rshA.getSize().y / 2);
    rshA.setRotation(visA.sprite.getRotation());
    rshA.setPosition(posA.x + rshA.getSize().x / 2, posA.y + rshA.getSize().y / 2); 
    
    sf::RectangleShape rshB;
    rshB.setTextureRect(sf::IntRect(visB.sprite.getGlobalBounds()));
    rshB.setSize(sf::Vector2f(visB.sprite.getLocalBounds().width * visB.sprite.getScale().x,
        visB.sprite.getLocalBounds().height * visB.sprite.getScale().y));
    rshB.setOrigin(rshB.getSize().x / 2, rshB.getSize().y / 2);
    rshB.setRotation(visB.sprite.getRotation());
    rshB.setPosition(posB.x + rshB.getSize().x / 2, posB.y + rshB.getSize().y / 2);

    colA.rectangle = sf::IntRect(rshA.getGlobalBounds());
    colB.rectangle = sf::IntRect(rshB.getGlobalBounds());

    if (touch(colA.rectangle, colB.rectangle)) {
        //printf("TOuch \n");
        return CollisionType::TOUCH;
    }
    if (colA.rectangle.intersects(colB.rectangle)) {
        //printf("Kolizja \n");
        return CollisionType::INTERSECT;
    }

    return CollisionType::NONE;
}


bool CollisionSystem::touch(const sf::IntRect& s, const sf::IntRect& r) {
    bool left = s.left == r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool right = s.left < r.left + r.width && s.left + s.width == r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool down = s.left < r.left + r.width && s.left + s.width > r.left && s.top == r.top + r.height && s.top + s.height > r.top;
    bool up = s.left < r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height == r.top;

    return left || right || down || up;
}
#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
#include "CollisionType.h"
#include "Collision.h"
#include "Position.h"
#include "Visual.h"

class CollisionSystem : public System {
public:
	CollisionSystem();

	void update(long gameFrame, float delta, World* world);

private :
	CollisionType intersects(const Position& posA, Collision& colA, const Visual& visA, const Position& posB, Collision& colB, const Visual& visB);
};

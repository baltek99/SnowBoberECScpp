#pragma once
#include "CollisionType.h"
#include "ObstacleType.h"

struct CollisionResponse {
public:
	int collidingEntityId;
	CollisionType collisionType;
	ObstacleType obstacle;

	CollisionResponse(int colEntityId, CollisionType colType, ObstacleType obsType);
};


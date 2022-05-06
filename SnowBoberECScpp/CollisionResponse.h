#pragma once
#include "Component.h"
#include "CollisionType.h"
#include "ObstacleType.h"

struct CollisionResponse : public Component {
public:
	int collidingEntityId;
	CollisionType collisionType;
	ObstacleType obstacle;

	CollisionResponse(int colEntityId, CollisionType colType, ObstacleType obsType);
};


#include "CollisionResponse.h"

CollisionResponse::CollisionResponse(int colEntityId, CollisionType colType, ObstacleType obsType) 
	: collidingEntityId(colEntityId), collisionType(colType), obstacle(obsType) {
}

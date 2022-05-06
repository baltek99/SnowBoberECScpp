#include "CollisionResponse.h"

CollisionResponse::CollisionResponse(int colEntityId, CollisionType colType, ObstacleType obsType) 
	: Component(CmpId::COLLISION_RESPONSE), collidingEntityId(colEntityId), collisionType(colType), obstacle(obsType) {
}

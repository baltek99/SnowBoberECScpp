#pragma once
#include "System.h"
#include "Lives.h"

class TexturesManager;

class PlayerCollisionSystem : public System {
public:
	PlayerCollisionSystem(const TexturesManager* texManager);

	void update(long gameFrame, float delta, World* world);
private :
	const TexturesManager* textures;

	void removeLifeOrKill(World* world, int entity, Lives& liv, int score);
};


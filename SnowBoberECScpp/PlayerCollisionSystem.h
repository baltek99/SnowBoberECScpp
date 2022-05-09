#pragma once
#include "System.h"
#include "Lives.h"

class TexturesManager;

class PlayerCollisionSystem : public System {
public:
	PlayerCollisionSystem(TexturesManager* texManager);

	void update(long gameFrame, float delta, World* world);
private :
	TexturesManager* textures;

	void removeLifeOrKill(World* world, int entity, Lives& liv, int score);
};


#pragma once
#include "System.h"
#include "Lives.h"

class TexturesManager;
class Game;

class PlayerCollisionSystem : public System {
public:
	PlayerCollisionSystem(const TexturesManager* texManager, Game* game_);

	void update(long gameFrame, float delta, World* world);
private :
	const TexturesManager* textures;
	Game* game;

	void removeLifeOrKill(World* world, int entity, Lives& liv, int score, int obstacleId);
};

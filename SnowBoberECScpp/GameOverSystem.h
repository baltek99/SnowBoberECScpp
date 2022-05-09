#pragma once
#include "System.h"

class Game;

class GameOverSystem : public System {
private :
	bool pcExist;
	Game* game;
public:
	GameOverSystem(Game* game_);

	void update(long gameFrame, float delta, World* world);
};


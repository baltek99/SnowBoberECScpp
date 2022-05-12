#pragma once
#include "System.h"

class InputManager;
class Game;

class TextBoxInputSystem : public System {
private: 
	InputManager* inputManager;
	Game* game;
public:
	TextBoxInputSystem(InputManager* manager, Game* game_);

	void update(long gameFrame, float delta, World* world);
};


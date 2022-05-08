#pragma once
#include "System.h"
#include <SFML/Graphics.hpp>

class InputManager;
class TexturesManager;

class PlayerControlledSystem : public System {
public:
	TexturesManager* textures;
	InputManager* inputManager;
	const sf::Event& actualEvent;

	PlayerControlledSystem(const sf::Event& event, TexturesManager* texturesManager, InputManager* inputManager_);

	void update(long gameFrame, float delta, World* world);
};


#pragma once
#include "System.h"
#include <SFML/Graphics.hpp>

class RenderSystem : public System {
public:
	sf::RenderWindow& window;

	RenderSystem(sf::RenderWindow& win);

	virtual void update(long gameFrame, float delta, World* world);
};


#pragma once
#include <SFML/Graphics.hpp>
#include "System.h"
class TextBoxRenderSystem : public System {
public:
	sf::RenderWindow& window;

	TextBoxRenderSystem(sf::RenderWindow& win);

	void update(long gameFrame, float delta, World* world);
};


#pragma once
#include "System.h"
#include <SFML/Graphics.hpp>

class ScoreRenderSystem : public System {
public:
	sf::RenderWindow& window;
	sf::Text text;
	sf::Font font;

	ScoreRenderSystem(sf::RenderWindow& win);

	void update(long gameFrame, float delta, World* world);
};


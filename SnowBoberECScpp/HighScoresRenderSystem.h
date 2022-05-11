#pragma once
#include "System.h"
#include <SFML/Graphics.hpp>

class HighScoresRenderSystem : public System {
public:
	sf::RenderWindow& window;
	sf::Text text;
	sf::Font font;

	HighScoresRenderSystem(sf::RenderWindow& win);

	void update(long gameFrame, float delta, World* world);
};


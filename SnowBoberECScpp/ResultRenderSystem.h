#pragma once
#include "System.h"
#include <SFML/Graphics.hpp>

class ResultRenderSystem : public System {
public:
	sf::RenderWindow& window;
	sf::Text text;
	sf::Font font;

	ResultRenderSystem(sf::RenderWindow& win);

	void update(long gameFrame, float delta, World* world);
};


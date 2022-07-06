#pragma once
#include <SFML/Graphics.hpp>

struct Visual {
public:
	sf::Sprite sprite;
	bool isVisible;

	Visual(const sf::Texture& texture, float scaleX, float scaleY);

	Visual(const sf::Texture& texture, float scaleX, float scaleY, bool visible);
};

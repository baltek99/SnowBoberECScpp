#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

struct Visual : public Component {
public:
	sf::Sprite sprite;

	Visual(const sf::Texture& texture, float scaleX, float scaleY);
};


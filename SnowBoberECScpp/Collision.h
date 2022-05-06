#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "ObstacleType.h"

struct Collision : public Component {
public:
	int width;
	int height;
	ObstacleType type;
	sf::IntRect rectangle;

	Collision(int width_, int height_, ObstacleType type_);
};

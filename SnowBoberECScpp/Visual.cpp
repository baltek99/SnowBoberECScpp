#include "Visual.h"

Visual::Visual(const sf::Texture& texture, float scaleX, float scaleY) : Component(CmpId::VISUAL) {
	sprite.setTexture(texture);
	sprite.setScale(scaleX, scaleY);
	sprite.setRotation(0);
}

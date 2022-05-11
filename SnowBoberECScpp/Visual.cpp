#include "Visual.h"

Visual::Visual(const sf::Texture& texture, float scaleX, float scaleY) : Component(CmpId::VISUAL) {
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setScale(scaleX, scaleY);
	sprite.setRotation(0);
	isVisible = true;
}

Visual::Visual(const sf::Texture& texture, float scaleX, float scaleY, bool visible) : Component(CmpId::VISUAL) {
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setScale(scaleX, scaleY);
	sprite.setRotation(0);
	isVisible = visible;
}

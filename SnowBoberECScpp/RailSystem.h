#pragma once
#include "System.h"

class TexturesManager;

class RailSystem : public System {
private:
	const TexturesManager* textures;
public:
	RailSystem(const TexturesManager* texManager);

	void update(long gameFrame, float delta, World* world);
};

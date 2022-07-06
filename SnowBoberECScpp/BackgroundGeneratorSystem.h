#pragma once
#include "System.h"

class BackgroundGeneratorSystem : public System {
public:
	void update(long gameFrame, float delta, World* world);
};

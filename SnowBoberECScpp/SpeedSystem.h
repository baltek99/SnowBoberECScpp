#pragma once
#include "System.h"
class SpeedSystem : public System {
public:
	void update(long gameFrame, float delta, World* world);
};


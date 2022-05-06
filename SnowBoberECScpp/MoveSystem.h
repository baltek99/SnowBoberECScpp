#pragma once
#include "System.h"
class MoveSystem : public System {
public:
	void update(long gameFrame, float delta, World* world);
};


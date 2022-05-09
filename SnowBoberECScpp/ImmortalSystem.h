#pragma once
#include "System.h"

class ImmortalSystem : public System {
private:
	int initialImmortalDurationVal;
	int immortalDuration;

public:
	ImmortalSystem();

	void update(long gameFrame, float delta, World* world);
};


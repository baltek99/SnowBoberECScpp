#pragma once
#include "System.h"
class SpeedSystem : public System {
private :
	int obstacleSpeed = -3;
public:
	void update(long gameFrame, float delta, World* world);
};


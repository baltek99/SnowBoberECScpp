#pragma once

class World;

class System { 
public:
	virtual void update(long gameFrame, float delta, World* world) = 0;
};

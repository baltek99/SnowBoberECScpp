#pragma once
#include "System.h"

class TexturesManager;

class JumpSystem : public System {
public:
    TexturesManager* textures;
    int jumpHeight;
    float duration;
    float rotationSpeed;
    int speedCount;
    int frame;

    JumpSystem(TexturesManager* texturesManager);

	void update(long gameFrame, float delta, World* world);
};


#pragma once
#include "System.h"

class TexturesManager;

class JumpSystem : public System {
public:
    const TexturesManager* textures;
    int jumpHeight;
    float duration;
    float rotationSpeed;
    float ollieUpSpeed;
    float ollieDownSpeed;
    int speedCount;
    int frame;

    JumpSystem(const TexturesManager* texturesManager);

	void update(long gameFrame, float delta, World* world);
};

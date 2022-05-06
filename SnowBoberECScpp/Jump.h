#pragma once
#include "Component.h"

struct Jump : public Component {
public :
	float startJumpFrame;
	int jumpFrom;

	Jump();
};


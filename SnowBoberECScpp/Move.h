#pragma once
#include "Component.h"
struct Move : public Component {
public :
	float speed;

	Move(float speed_);
};


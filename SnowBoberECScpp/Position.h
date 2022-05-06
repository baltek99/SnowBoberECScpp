#pragma once
#include "Component.h"
struct Position : public Component {
public :
	int x, y;

	Position(int x_, int y_);
};


#pragma once
#include "Component.h"
struct ScoreBind : public Component {
public:
	int playerId;

	ScoreBind(int playerId_);
};


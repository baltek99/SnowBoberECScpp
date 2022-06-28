#pragma once
#include "PlayerState.h"
#include <string>

struct PlayerControlled {
public:
	PlayerState playerState;
	std::string name;

	PlayerControlled(PlayerState state, std::string name_);
};


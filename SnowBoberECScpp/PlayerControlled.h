#pragma once
#include "Component.h"
#include "PlayerState.h"
#include <string>

struct PlayerControlled : public Component {
public:
	PlayerState playerState;
	std::string name;

	PlayerControlled(PlayerState state, std::string name_);
};


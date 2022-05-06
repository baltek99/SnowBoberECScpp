#pragma once
#include "Component.h"
#include <vector>
#include <optional>

struct Lives : public Component {
public:
	int lives;
	std::vector<std::optional<int>> livesIds;

	Lives(std::vector<std::optional<int>> livesIds_);
};


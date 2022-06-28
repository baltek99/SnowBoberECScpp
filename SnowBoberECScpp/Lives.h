#pragma once
#include <vector>
#include <optional>

struct Lives {
public:
	int lives;
	std::vector<std::optional<int>> livesIds;

	Lives(std::vector<std::optional<int>> livesIds_);
};


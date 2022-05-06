#include "Lives.h"

Lives::Lives(std::vector<std::optional<int>> livesIds_) : Component(CmpId::LIVES) {
	livesIds = livesIds_;
}
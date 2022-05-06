#include "PlayerControlled.h"

PlayerControlled::PlayerControlled(PlayerState state, std::string name_) : Component(CmpId::PLAYER_CONTROLLED), playerState(state), name(name_) {
}

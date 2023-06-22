#include "venom_close_range_attack.h"
#include "../../../zombie_states/zombie_state.h"
#include "../../../configuration.h"

VenomCloseRange::VenomCloseRange() : damage(CONFIGURATION.get_venom_damage_close_range()) {}

ZombieState* VenomCloseRange::attack(ZombieState *state, Soldier* soldier_to_attack, float time) {
    return state->attack_soldier(soldier_to_attack, damage, time);
}

bool VenomCloseRange::are_you_long_range_attack() {
    return false;
}
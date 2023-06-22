#include "venom_long_range_attack.h"
#include "../../../soldier.h"
#include "../../../zombie_states/zombie_state.h"

VenomLongRange::VenomLongRange() : damage(CONFIGURATION.get_venom_damage_long_range()) {}

ZombieState *VenomLongRange::attack(ZombieState *state, Soldier* soldier_to_attack, float time) {
    x_pos_explosion = soldier_to_attack -> get_x_pos();
    y_pos_explosion = soldier_to_attack -> get_y_pos();
    return state->attack_soldier(soldier_to_attack, damage, time);
}

bool VenomLongRange::are_you_long_range_attack() {
    return true;
}
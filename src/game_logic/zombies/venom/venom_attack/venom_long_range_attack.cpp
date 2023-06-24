#include "venom_long_range_attack.h"
#include "../../../soldier.h"
#include "../../../zombie_states/zombie_state.h"

VenomLongRange::VenomLongRange() : damage(CONFIGURATION.get_venom_damage_long_range()) {}

ZombieState *VenomLongRange::attack(ZombieState *state, Soldier* soldier_to_attack, float time) {
    x_pos_explosion = soldier_to_attack -> get_x_pos();
    y_pos_explosion = soldier_to_attack -> get_y_pos();
    ZombieState* new_state = state->attack_soldier_long_range(soldier_to_attack, damage, time);
    return new_state;
}

std::vector<std::int16_t> VenomLongRange::get_pos_explosion() {
    std::vector<std::int16_t> explosion_pos;
    explosion_pos.push_back(x_pos_explosion);
    explosion_pos.push_back(y_pos_explosion);
    return explosion_pos;
}

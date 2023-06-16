#include "venom_close_range_attack.h"
#include "../zombie_states/zombie_state.h"

ZombieState* VenomCloseRange::attack(ZombieState *state, Soldier* soldier_to_attack, float time) {
    return state->attack_soldier(soldier_to_attack, damage, time);
}
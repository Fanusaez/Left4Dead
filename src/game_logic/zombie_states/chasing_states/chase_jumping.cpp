#include "chase_jumping.h"


ZombieState *ChaseJumping::chase(ZombieState *state, Chaser &chaser, std::int16_t x_pos_chase, std::int16_t y_pos_chase,
                                 float time) {
    return state->chase_soldier_jumping(chaser, x_pos_chase, y_pos_chase, time);
}

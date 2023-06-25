#include "chase_walking.h"

ChaseWalking::ChaseWalking() {}

ZombieState *ChaseWalking::chase(ZombieState *state, Chaser& chaser,std::int16_t x_pos_chase, std::int16_t y_pos_chase, float time) {
    return state->chase_soldier(chaser, x_pos_chase, y_pos_chase, time);
}

bool ChaseWalking::jumping() {
    return false;
}
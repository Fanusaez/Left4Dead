#include "chase_running.h"

ZombieState *ChaseRunning::chase(ZombieState *state, Chaser &chaser, std::int16_t x_pos_chase, std::int16_t y_pos_chase,
                                 float time) {
    return state -> chase_soldier_running(chaser, x_pos_chase, y_pos_chase, time);
}

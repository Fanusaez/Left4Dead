#ifndef CHASE_STATE_H_
#define CHASE_STATE_H_
#include <cstdint>
class ZombieState;
class Chaser;

class ChaseState {
public:
    virtual ZombieState* chase(ZombieState* state,
                       Chaser& chaser,
                       std::int16_t x_pos_chase,
                       std::int16_t y_pos_chase,
                       float time) = 0;
};
#endif  // CHASE_STATE_H_

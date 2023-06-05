#ifndef CHASE_JUMPING_H_
#define CHASE_JUMPING_H_

#include "chase_state.h"
#include "../zombie_state.h"

class ChaseJumping : public ChaseState {
private:

public:

    ZombieState* chase(ZombieState* state,
                       Chaser& chaser,
                       std::int16_t x_pos_chase,
                       std::int16_t y_pos_chase,
                       float time) override;
};


#endif  // CHASE_JUMPING_H_

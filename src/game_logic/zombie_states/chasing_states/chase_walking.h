#ifndef CHASE_WALKING_H_
#define CHASE_WALKING_H_

#include "chase_state.h"
#include "../zombie_state.h"

class ChaseWalking : public ChaseState {

private:

public:

ChaseWalking();

ZombieState* chase(ZombieState* state,
                   Chaser& chaser,
                   std::int16_t x_pos_chase,
                   std::int16_t y_pos_chase,
                   float time) override;

bool jumping() override;

};


#endif  // CHASE_WALKING_H_

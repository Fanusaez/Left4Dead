#ifndef RUNNING_H_
#define RUNNING_H_

#include "chase_state.h"
#include "../zombie_state.h"

class ChaseRunning : public ChaseState {
private:

public:

    ZombieState* chase(ZombieState* state,
                       Chaser& chaser,
                       std::int16_t x_pos_chase,
                       std::int16_t y_pos_chase,
                       float time) override;
};


#endif  // RUNNING_H_

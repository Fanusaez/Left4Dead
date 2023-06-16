#ifndef  VENOM_LONG_RANGE_ATTACK_H_
#define  VENOM_LONG_RANGE_ATTACK_H_

#include "zombie_attack.h"

class VenomLongRange : public ZombieAttack {
private:
    std::int16_t damage = 15;
    std::int16_t x_pos_explosion;
    std::int16_t y_pos_explosion;

public:

    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time) override;

};


#endif  // VENOM_LONG_RANGE_ATTACK_H_

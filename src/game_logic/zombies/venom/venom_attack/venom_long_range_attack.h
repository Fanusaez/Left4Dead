#ifndef  VENOM_LONG_RANGE_ATTACK_H_
#define  VENOM_LONG_RANGE_ATTACK_H_

#include "venom_attack.h"

class VenomLongRange : public VenomAttack {
private:
    std::int16_t damage;
    std::int16_t x_pos_explosion;
    std::int16_t y_pos_explosion;

public:
    VenomLongRange();
    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time) override;

};


#endif  // VENOM_LONG_RANGE_ATTACK_H_

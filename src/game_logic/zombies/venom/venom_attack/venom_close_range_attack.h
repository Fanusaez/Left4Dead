#ifndef VENOM_CLOSE_RANGE_ATTACK_H_
#define VENOM_CLOSE_RANGE_ATTACK_H_

#include "venom_attack.h"

class VenomCloseRange : public VenomAttack {

private:
    std::int16_t damage;

public:
    VenomCloseRange();
    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time) override;
    bool are_you_long_range_attack() override;
};


#endif  // VENOM_CLOSE_RANGE_ATTACK_H_

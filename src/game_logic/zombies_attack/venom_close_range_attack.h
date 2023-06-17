#ifndef LEFT4DEAD_VENOM_CLOSE_RANGE_ATTACK_H
#define LEFT4DEAD_VENOM_CLOSE_RANGE_ATTACK_H

#include "zombie_attack.h"

class VenomCloseRange : public ZombieAttack {

private:
    std::int16_t damage = 30;

public:
    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time) override;

};


#endif //LEFT4DEAD_VENOM_CLOSE_RANGE_ATTACK_H

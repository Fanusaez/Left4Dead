#ifndef VENOM_CLOSE_RANGE_ATTACK_H_
#define VENOM_CLOSE_RANGE_ATTACK_H_

#include <cstdint>

class ZombieState;
class Soldier;

class VenomCloseRange {

private:
    std::int16_t damage;

public:
    VenomCloseRange();

    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time);

};


#endif  // VENOM_CLOSE_RANGE_ATTACK_H_

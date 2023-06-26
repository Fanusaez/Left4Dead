#ifndef  VENOM_LONG_RANGE_ATTACK_H_
#define  VENOM_LONG_RANGE_ATTACK_H_

#include <vector>
#include <cstdint>

class ZombieState;
class Soldier;

class VenomLongRange {
private:
    float last_time_attacked = -1;
    float time_to_attack_again = 0.8;
    std::int16_t damage;
    std::int16_t x_pos_explosion;
    std::int16_t y_pos_explosion;

public:
    VenomLongRange();
    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time);
    std::vector<std::int16_t> get_pos_explosion();
    bool time_to_attack(float time);
};

#endif  // VENOM_LONG_RANGE_ATTACK_H_

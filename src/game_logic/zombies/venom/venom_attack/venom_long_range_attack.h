#ifndef  VENOM_LONG_RANGE_ATTACK_H_
#define  VENOM_LONG_RANGE_ATTACK_H_

#include <vector>
#include <cstdint>

class ZombieState;
class Soldier;

class VenomLongRange {
private:
    const std::int16_t id;
    std::int16_t damage;
    float time_to_attack_again;
    float last_time_attacked;
    std::int16_t x_pos_explosion;
    std::int16_t y_pos_explosion;

public:

    explicit VenomLongRange(std::int16_t id);
    ZombieState* attack(ZombieState *state, Soldier* soldier_to_attack, float time);
    std::vector<std::int16_t> get_pos_explosion();
    bool time_to_attack(float time);
    std::int16_t get_id_attack_long();
};

#endif  // VENOM_LONG_RANGE_ATTACK_H_

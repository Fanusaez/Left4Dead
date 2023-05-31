#ifndef ATTACKING_H_
#define ATTACKING_H_

#include "zombie_state.h"
#include "walking.h"

class Attacking : public ZombieState {

private:
    float attack_speed = 0.3;
    float waiting_time_to_attack = 0.2;
    float start_time;

public:
    Attacking(GameObject* closest_soldier, std::int16_t damage, float time);

    ZombieState* chase_soldier(Zombie* zombie,
                               std::int16_t &x_pos,
                               std::int16_t &y_pos,
                               std::int16_t& x_new_pos,
                               std::int16_t& y_new_pos,
                               GameObject* closest_soldier,
                               GameMap& map,
                               float time) override;

    ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

    ZombieState* being_attacked(float time) override;

    ZombieState* die(float time) override;

    void set_speed(float speed) override;

    bool time_to_attack(float time);

};


#endif //ATTACKING_H_

#ifndef ZOMBIE_BEING_ATTACKED_H_
#define ZOMBIE_BEING_ATTACKED_H_

#include "attacking.h"

class ZombieBeingAttacked : public ZombieState {

private:
    float time_stop_being_attacked = 0.3;
    float start_time;

public:
    ZombieBeingAttacked(float time);

     ZombieState* chase_soldier(Zombie* zombie,
                                       float &x_pos,
                                       float &y_pos,
                                       std::int16_t &x_new_pos,
                                       std::int16_t &y_new_pos,
                                       GameObject* closest_soldier,
                                       GameMap& map,
                                       float time) override;

     ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

     ZombieState* being_attacked(float time) override;

     ZombieState* die(float time) override;

     bool time_to_stop_being_attacked(float time);

     void set_speed(float speed) override;

};


#endif  // ZOMBIE_BEING_ATTACKED_H_

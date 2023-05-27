#ifndef ZOMBIEDEAD_H_
#define ZOMBIEDEAD_H_

#include "attacking.h"

class ZombieDead : public ZombieState {
private:
    // float time_to_disappear????
public:
    ZombieState* chase_soldier(Zombie* zombie,
                               float &x_pos,
                               float &y_pos,
                               std::int16_t &x_new_pos,
                               std::int16_t &y_new_pos,
                               GameObject* closest_soldier,
                               GameMap& map,
                               float time) override;

    ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;


    void set_speed(float speed) override;

};

#endif  // ZOMBIEDEAD_H_

#ifndef WALKING_H_
#define WALKING_H_

#include "../map.h"
#include "attacking.h"
#include "zombie_dead.h"
#include "zombie_being_attacked.h"

class Walking : public ZombieState {

private:
    std::int16_t walker_speed = 1;
    float waiting_time_to_walk = 0.2;
    float start_time;
    std::int16_t& x_pos;
    std::int16_t& y_pos;
public:

Walking(Zombie* zombie,
        std::int16_t& x_pos,
        std::int16_t& y_pos,
        std::int16_t &x_new_pos,
        std::int16_t &y_new_pos,
        GameObject* closest_soldier,
        GameMap& map,
        float time);

ZombieState* chase_soldier(Zombie* zombie,
                           std::int16_t &x_pos,
                           std::int16_t &y_pos,
                           std::int16_t &x_new_pos,
                           std::int16_t &y_new_pos,
                           GameObject* closest_soldier,
                           GameMap& map,
                           float time) override;

ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

ZombieState* being_attacked(float time) override;

ZombieState* die(float time) override;

bool time_to_walk(float time);

void set_speed(float speed) override;
};

#endif  // WALKING_H_

#ifndef WALKING_H_
#define WALKING_H_

#include "attacking.h"
#include "zombie_dead.h"
#include "zombie_being_attacked.h"
#include "../chaser.h"

class Walking : public ZombieState {

private:
    std::int16_t walker_speed = 1;
    float waiting_time_to_walk = 0.2;
    float start_time;

public:

Walking(Chaser& chaser,
        std::int16_t x_pos_chase,
        std::int16_t y_pos_chase,
        float time);

ZombieState* chase_soldier(Chaser& chaser,
                           std::int16_t x_pos_chase,
                           std::int16_t y_pos_chase,
                           float time) override;

ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

ZombieState* being_attacked(float time) override;

ZombieState* die(float time) override;

bool time_to_walk(float time);

void set_speed(float speed) override;
};

#endif  // WALKING_H_

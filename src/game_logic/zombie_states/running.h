#ifndef RUNNING_H
#define RUNNING_H

#include "zombie_idle.h"

class Running : public ZombieState {
private:
    float waiting_time_to_walk = 0.1;
    float start_time;

public:

    Running(Chaser& chaser,
            std::int16_t x_pos_chase,
            std::int16_t y_pos_chase,
            float time);

    ZombieState* chase_soldier(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) override;

    ZombieState* chase_soldier_running(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) override;

    ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

    ZombieState* being_attacked(float time) override;

    ZombieState* die(float time) override;

    bool time_to_walk(float time);

    void set_speed(float speed) override;
};


#endif  // RUNNING_H

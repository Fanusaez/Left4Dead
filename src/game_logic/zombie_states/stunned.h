#ifndef STUNNED_H_
#define STUNNED_H_

#include "zombie_idle.h"

class Stunned : public ZombieState {

private:
    float waiting_time_to_walk = 0.2;
    float waiting_time_to_normal = 10; // 10 segundos para dejar de estar stunneado
    float start_time;
    float last_time_moved = - 1;

public:

    Stunned(float time);

    ZombieState* chase_soldier(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) override;

    ZombieState* chase_soldier_running(Chaser& chaser,
                                       std::int16_t x_pos_chase,
                                       std::int16_t y_pos_chase,
                                       float time) override;

    ZombieState* chase_soldier_jumping(Chaser& chaser,
                                       std::int16_t x_pos_chase,
                                       std::int16_t y_pos_chase,
                                       float time) override;

    ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

    ZombieState* being_attacked(float time) override;

    ZombieState* die(float time) override;

    ZombieState* get_stunned(float time) override;

    bool time_to_walk(float time);

    bool time_stop_being_stunned(float time);

    void set_speed(float speed) override;
};


#endif  // STUNNED_H_

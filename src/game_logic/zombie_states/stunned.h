#ifndef STUNNED_H_
#define STUNNED_H_

#include "zombie_idle.h"

class Stunned : public ZombieState {

private:
    float waiting_time_to_normal;
    float waiting_time_to_walk;
    float start_time;
    float last_time_moved = - 1;

public:

    Stunned(float time);

    ZombieState* update(float time) override;

    ZombieState* chase_soldier(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) override;

    ZombieState* chase_soldier_running(Chaser& chaser,
                                       std::int16_t x_pos_chase,
                                       std::int16_t y_pos_chase,
                                       float time) override;

    ZombieState* chase_soldier_jumping(Chaser& chaser,
                                       Soldier* soldier,
                                       std::int16_t damage,
                                       std::int16_t x_pos_chase,
                                       std::int16_t y_pos_chase,
                                       float time) override;

    ZombieState* attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) override;

    ZombieState* being_attacked(float time) override;

    ZombieState* die(float time) override;

    ZombieState* get_stunned(float time) override;

    bool time_to_walk(float time);

    ZombieState* scream(GameMap &map, std::int16_t zombies_to_create, float time) override;

    bool time_stop_being_stunned(float time);

    void set_speed(float speed) override;

    void set_long_range() override;
};


#endif  // STUNNED_H_

#ifndef WALKING_H_
#define WALKING_H_

#include "zombie_state.h"

class Walking : public ZombieState {

private:
    float waiting_time_to_walk;
    float last_time_moved = - 1;

public:

Walking(Chaser& chaser,
        std::int16_t x_pos_chase,
        std::int16_t y_pos_chase,
        float time);

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
                                   std::int16_t x_pos_chase,
                                   std::int16_t y_pos_chase,
                                   float time) override;

ZombieState* attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) override;

ZombieState* attack_soldier_long_range(Soldier* closest_soldier, std::int16_t damage, float time) override;

ZombieState* being_attacked(float time) override;

ZombieState* die(float time) override;

ZombieState* get_stunned(float time) override;

ZombieState* scream(GameMap &map, std::int16_t zombies_to_create, float time) override;

bool time_to_move(float time);

void set_speed(float speed) override;

};

#endif  // WALKING_H_

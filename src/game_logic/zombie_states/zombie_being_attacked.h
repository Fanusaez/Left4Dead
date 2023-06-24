#ifndef ZOMBIE_BEING_ATTACKED_H_
#define ZOMBIE_BEING_ATTACKED_H_

#include "attacking.h"

class ZombieBeingAttacked : public ZombieState {

private:
    float start_time;
    float time_stop_being_attacked;

public:
    ZombieBeingAttacked(float time);

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

    ZombieState* scream(GameMap &map, std::int16_t zombies_to_create, float time) override;

     bool time_to_stop_being_attacked(float time);

     void set_speed(float speed) override;

     void set_long_range() override;

};


#endif  // ZOMBIE_BEING_ATTACKED_H_

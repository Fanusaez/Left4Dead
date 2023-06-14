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

    Attacking(Soldier* closest_soldier, std::int16_t damage, float time);

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

    void set_speed(float speed) override;

    bool time_to_attack(float time);

};


#endif //ATTACKING_H_

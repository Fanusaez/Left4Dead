#ifndef SCREAMING_H_
#define SCREAMING_H_

#include "zombie_state.h"
#include "zombie_idle.h"

class Screaming : public ZombieState{
private:
    float waiting_time_to_stop_screaming = 1;
    float last_time_screamed = - 1;

public:

    Screaming(GameMap& map, std::int16_t zombies_to_create, float time);

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

    bool time_to_walk(float time);

    bool time_stop_screaming(float time);

    void set_speed(float speed) override;

};


#endif //SCREAMING_H_

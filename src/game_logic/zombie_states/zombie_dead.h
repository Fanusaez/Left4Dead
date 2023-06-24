#ifndef ZOMBIEDEAD_H_
#define ZOMBIEDEAD_H_

#include "attacking.h"

class ZombieDead : public ZombieState {
private:

public:
     explicit ZombieDead(float time);

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

    ZombieState* get_stunned(float time) override;

    ZombieState* die(float time) override;

    ZombieState* scream(GameMap &map, std::int16_t zombies_to_create, float time) override;

    void set_speed(float speed) override;

    void set_long_range() override;

};

#endif  // ZOMBIEDEAD_H_

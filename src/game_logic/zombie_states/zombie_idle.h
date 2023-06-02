#ifndef ZOMBIEIDLE_H
#define ZOMBIEIDLE_H

#include "walking.h"

class ZombieIdle : public ZombieState {
public:
    ZombieState* chase_soldier(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) override;

    ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) override;

    ZombieState* being_attacked(float time) override;

    ZombieState* die(float time) override;

    void set_speed(float speed) override;
};


#endif //ZOMBIEIDLE_H

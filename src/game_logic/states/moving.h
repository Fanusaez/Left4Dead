#ifndef MOVING_H_
#define MOVING_H_

#include "idle.h"
class Moving : public State {
private:
    float waiting_time_to_move = 0.2;
    float start_time;
    Soldier& soldier;
public:
    Moving(Soldier& soldier, std::int16_t direction, float start_time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float start_time) override;
    State* being_attacked(float time) override;
    State* die(float time) override;
    State* revive(float time) override;
    State* throw_explosive_grenade(float time) override;

    bool time_to_move(float time);
};


#endif //MOVING_H_

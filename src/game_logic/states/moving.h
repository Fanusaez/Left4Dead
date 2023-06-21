#ifndef MOVING_H_
#define MOVING_H_

#include "state.h"

class Moving : public State {
private:
    Soldier& soldier;
    std::int16_t direction;
    float waiting_time_to_move;
    float last_time_moved;

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
    State* throw_smoke_grenade(float time) override;
    State* call_air_strike(float time) override;
    State* stop_action() override;

    bool time_to_move(float time);
};


#endif //MOVING_H_

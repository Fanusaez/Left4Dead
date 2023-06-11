#ifndef DEAD_H_
#define DEAD_H_

#include "state.h"

class Dead : public State {

private:
    float time_to_revive = 10;
    float start_time;

public:

    Dead(float time_of_death);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float time) override;
    State* being_attacked(float time) override;
    State* die(float time) override;
    State* revive(float time) override;
    State* throw_explosive_grenade(float time) override;
    State* throw_smoke_grenade(float time) override;
    State* call_air_strike(float time) override;
    State* stop_action() override;
    bool able_to_revive(float time);

};


#endif //DEAD_H_

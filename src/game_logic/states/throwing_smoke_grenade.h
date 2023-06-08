#ifndef THROWING_SMOKE_GRENADE_H_
#define THROWING_SMOKE_GRENADE_H_

#include "state.h"
#include "idle.h"

class ThrowingSmokeGrenade : public State {
private:
    float start_time;
    float duration_of_throwing_granade = 0.2;

public:

    explicit ThrowingSmokeGrenade(float time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float start_time) override;
    State* being_attacked(float time) override;
    State* die(float time) override;
    State* revive(float time) override;
    State* throw_explosive_grenade(float time) override;
    State* throw_smoke_grenade(float time) override;
    bool time_stop_throwing(float time);
    State* stop_action() override;
};


#endif //THROWING_SMOKE_GRENADE_H_

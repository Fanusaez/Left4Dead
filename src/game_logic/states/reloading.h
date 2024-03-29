#ifndef RELOAD_H_
#define RELOAD_H_

#include "state.h"

class Reloading : public State {
private:
    Weapon* weapon;
    float start_time;
    float waiting_time_to_reload;

public:
    Reloading(Weapon* weapon, float time);

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

    bool time_to_relaod(float time);
};


#endif //RELOAD_H_

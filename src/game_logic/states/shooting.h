#ifndef SHOOTING_H_
#define SHOOTING_H_

#include "reloading.h"

class Shooting  : public State {
private:
    Soldier& soldier;
    Weapon* weapon;
    float waiting_time_to_shoot = 0.10;
    float start_time = -1;
public:
    Shooting(Soldier& soldier, Weapon* weapon, float start_time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float start_time) override;
    State* being_attacked(float time) override;
    State* die(float time) override;
    State* revive(float time) override;
    State* throw_explosive_grenade(float time) override;
    State* throw_smoke_grenade(float time) override;
    State* stop_action() override;

    bool time_to_shoot(float time);
};


#endif   // SHOOTING_H_
